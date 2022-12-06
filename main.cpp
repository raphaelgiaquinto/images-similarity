#include "main.hpp"


int main(int argc, char** argv) {

    if(argc < 3) {
        return EXIT_FAILURE;
    }

    cv::Mat origin;
    cv::Mat compared;

    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher  = cv::DescriptorMatcher::create ( "BruteForce-Hamming" );

    origin = cv::imread(argv[1], cv::IMREAD_COLOR);
    compared = cv::imread(argv[2], cv::IMREAD_COLOR);   

    cv::Size resize(480, 480);
    cv::resize(origin, origin, resize);
    cv::resize(compared, compared, resize);

    std::vector<cv::KeyPoint> keypointsOrigin, keypointsCompared;
    cv::Mat descriptorsOrigin, descriptorsCompared;

    detector->detect(origin ,keypointsOrigin);
    detector->detect(compared, keypointsCompared);

    descriptor->compute(origin, keypointsOrigin, descriptorsOrigin);
    descriptor->compute(compared, keypointsCompared, descriptorsCompared);

    std::vector<cv::DMatch> matches;

    matcher->match(descriptorsOrigin, descriptorsCompared, matches);

    double min_dist=10000, max_dist=0;

    for(int i = 0; i < descriptorsOrigin.rows; i++ ){
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    std::vector<cv::DMatch > good_matches;
    for(int i = 0; i < descriptorsOrigin.rows; i++){
        if(matches[i].distance <= min_dist * 1.10 ){
            good_matches.push_back(matches[i]);
        }
    }   

    std::cout << matches.size() << " matches | " << good_matches.size() << " good matches" << std::endl;
    double percent = ((double) good_matches.size() / (double) matches.size()) * 100.0;
    std::cout << percent << "\% percent of good matches" << std::endl;
    cv::Mat img_goodmatch;
    cv::drawMatches( origin, keypointsOrigin, compared, keypointsCompared, good_matches, img_goodmatch);
    cv::imshow ( "good match", img_goodmatch );
    cv::waitKey(0);
   
    return EXIT_SUCCESS;
}