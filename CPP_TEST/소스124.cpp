#include <nlohmann/json.hpp>
#include <iostream>

using nlohmann::json;

enum TaskState {
    TS_STOPPED,
    TS_RUNNING,
    TS_COMPLETED,
    TS_INVALID = -1,
};

NLOHMANN_JSON_SERIALIZE_ENUM(TaskState, {
  {TS_INVALID, nullptr},
  {TS_STOPPED, "stopped"},
  {TS_RUNNING, "running"},
  {TS_COMPLETED, "completed"},
    });
/*

Specializing enum conversion
By default, enum values are serialized to JSON as integers. In some cases this could result in undesired behavior. 
If an enum is modified or re-ordered after data has been serialized to JSON, the later de-serialized JSON data may 
be undefined or a different enum value than was originally intended.
It is possible to more precisely specify how a given enum is mapped to and from JSON as shown below:

*/
int main()
{      
    json j = TS_STOPPED;
    std::cout << j.dump() << std::endl;
    
}