#include "DefaultEngine.h"
#include "utils/file/read_file_to_string.h"
#include "utils/json/get_value.h"
#include "utils/json/parse_json.h"

void DefaultEngine::load_resources() {
    auto doc = json::parse_json(file::read_file_to_string("data/common_media.json"));

    using json::get_value;
    auto texturesMap = get_value<rapidjson::Value::ConstObject>(doc, "/textures");
    for(const auto& entry : texturesMap) {
        _resources->load_texture(get_value<const char *>(entry.name, ""), get_value<const char *>(entry.value, ""));
    }

    auto soundsMap = get_value<rapidjson::Value::ConstObject>(doc, "/sounds");
    for(const auto& entry : soundsMap) {
        _resources->load_sound(get_value<const char *>(entry.name, ""), get_value<const char *>(entry.value, ""));
    }

    auto musicMap = get_value<rapidjson::Value::ConstObject>(doc, "/music");
    for(const auto& entry : musicMap) {
        _resources->load_music(get_value<const char *>(entry.name, ""), get_value<const char *>(entry.value, ""));
    }
}
