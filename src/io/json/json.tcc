template<class T>
T json::detail::get_value_casted(const rapidjson::Value& root, cstring source) {
    auto value = get_value(root, source);

    // Despite the docs saying Is<> and Get<> work only on scalars,
    // this also works for ConstArray and ConstObject.
    if (!value->Is<T>()) {
        using namespace std::string_literals;
        throw ParseException{
                "Value on "s + source + " is not of type " + utils::demangle_type_name(typeid(T).name())
        };
    }
    return value->Get<T>();
}

template<typename T>
T json::get_value(const rapidjson::Value& root, cstring source) {
    return detail::get_value_casted<T>(root, source);
}

template<typename T>
std::vector<T> json::get_values(const rapidjson::Value& root, cstring source) {
    auto array = detail::get_value_casted<rapidjson::Value::ConstArray>(root, source);

    std::vector<T> vector;
    vector.reserve(array.Size());
    for (const auto& value : array) {
        vector.emplace_back(value.Get<T>());
    }
    return vector;
}
