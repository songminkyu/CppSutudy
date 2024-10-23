#include <singleheader/simdjson.h>

int main(void) {
    simdjson::dom::parser parser;
    simdjson::dom::element tweets;
    auto error = parser.load("twitter.json").get(tweets);
    if (error) { std::cerr << error << std::endl; return EXIT_FAILURE; }
    simdjson::dom::element res;

    /*    
    "search_metadata": {
    "completed_in": 0.087,
    "max_id": 505874924095815700,
    "max_id_str": "505874924095815681",
    "next_results": "?max_id=505874847260352512&q=%E4%B8%80&count=100&include_entities=1",
    "query": "%E4%B8%80",
    "refresh_url": "?since_id=505874924095815681&q=%E4%B8%80&include_entities=1",
    "count": 100,
    "since_id": 0,
    "since_id_str": "0"
  }
    
    */

    if ((error = tweets["search_metadata"]["completed_in"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;
    
    if ((error = tweets["search_metadata"]["max_id"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;

    if ((error = tweets["search_metadata"]["max_id_str"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;

    if ((error = tweets["search_metadata"]["query"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;


    if ((error = tweets["search_metadata"]["refresh_url"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;

    if ((error = tweets["search_metadata"]["count"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;

    if ((error = tweets["search_metadata"]["since_id"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;

    if ((error = tweets["search_metadata"]["since_id_str"].get(res))) {
        std::cerr << "could not access keys" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << res << " results." << std::endl;


}