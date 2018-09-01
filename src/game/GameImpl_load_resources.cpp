#include "GameImpl.h"
#include "io/files/files.h"
#include "io/json/get_value.h"
#include "io/json/parse_json.h"

void GameImpl::load_resources() {
    auto doc = json::parse_json(files::read_file_to_string("data/common_media.json"));

    using json::get_value;
    auto texturesMap = get_value<rapidjson::Value::ConstObject>(doc, "/textures");
    for (const auto& entry : texturesMap) {
        _engine->get_graphic().load_texture(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }

    auto soundsMap = get_value<rapidjson::Value::ConstObject>(doc, "/sounds");
    for (const auto& entry : soundsMap) {
        _engine->get_audio().load_sound(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }

    auto musicMap = get_value<rapidjson::Value::ConstObject>(doc, "/music");
    for (const auto& entry : musicMap) {
        _engine->load_music(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }
}
