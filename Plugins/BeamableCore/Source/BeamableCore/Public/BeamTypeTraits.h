#pragma once

#include <type_traits>

// Since Type Traits syntax sucks so much... whenever you need one, take a quick look around first...
// These are thanks too: https://stackoverflow.com/questions/50865095/how-to-check-if-a-type-is-a-type-parameter-for-template-class-in-c
template<typename Type, typename Template>
struct TIsTemplateParam : std::false_type {};

template<typename Type, template<typename...> class Template, typename... R>
struct TIsTemplateParam<Type, Template<Type, R...>> : std::true_type {};

template<int N, typename Type, typename Template>
struct TIsNthTemplateParam : std::false_type {};

template<int N, typename Type, template<typename...> class Template, typename... TplParams>
struct TIsNthTemplateParam<N, Type, Template<TplParams...>> : std::is_same<Type, std::tuple_element_t<N, std::tuple<TplParams...>>> {};

template<typename Type, typename Template>
using TIsFirstTemplateParam = TIsNthTemplateParam<0, Type, Template>;

template<typename Type, typename Template>
using TIsSecondTemplateParam = TIsNthTemplateParam<1, Type, Template>;