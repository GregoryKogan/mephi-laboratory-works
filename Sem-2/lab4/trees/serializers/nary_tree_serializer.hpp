//
// Created by Gregory Kogan on 27.05.2023.
//

#ifndef LAB4_NARY_TREE_SERIALIZER_HPP
#define LAB4_NARY_TREE_SERIALIZER_HPP

#include "../../trees/nary_tree.hpp"


namespace kogan {

    template <class T> class NaryTreeSerializer {
        static NaryTree<T>* deserialize_as_child(const std::string& serialized_tree, int max_children_data);
        static T read_until_open_bracket(const std::string& str);
        static std::string parse_content(const std::string& str);
        static Sequence<std::string>* parse_serialized_children(const std::string& serialized_children);
        static void append_parsed_children(
                NaryTree<T>* tree,
                const Sequence<std::string>* parsed_children,
                int max_children_data
        );

    public:
        static NaryTree<T>* deserialize(const std::string& serialized_tree);
    };

    template<class T>
    NaryTree<T> *NaryTreeSerializer<T>::deserialize(const std::string& serialized_tree) {
        std::istringstream iss(serialized_tree);
        int max_children_data; iss >> max_children_data;
        if (max_children_data < 1)
            throw InvalidArgumentException("max_children");

        std::string remaining_string;
        getline(iss, remaining_string);
        return deserialize_as_child(remaining_string, max_children_data);
    }

    template<class T>
    NaryTree<T> *NaryTreeSerializer<T>::deserialize_as_child(const std::string &serialized_tree, int max_children_data) {
        T root_value = read_until_open_bracket(serialized_tree);
        auto* result = new NaryTree<T>(root_value, max_children_data);

        Sequence<std::string>* parsed_children = parse_serialized_children(
                parse_content(serialized_tree)
        );

        append_parsed_children(result, parsed_children, max_children_data);

        delete parsed_children;
        return result;
    }

    template<class T>
    T NaryTreeSerializer<T>::read_until_open_bracket(const std::string &str) {
        std::string prefix;
        for (char symbol : str) {
            if (symbol == '(')
                break;
            prefix += symbol;
        }

        if (prefix.empty())
            throw InvalidArgumentException("serialized_tree");

        std::istringstream iss(prefix);
        T result; iss >> result;
        if (iss.fail())
            throw InvalidArgumentException("serialized_tree");
        return result;
    }

    template<class T>
    std::string NaryTreeSerializer<T>::parse_content(const std::string &str) {
        std::string content;
        size_t first_open_bracket_index = str.find('(');
        size_t last_close_bracket_index = str.rfind(')');
        for (size_t i = first_open_bracket_index; i <= last_close_bracket_index; ++i)
            content += str[i];
        return content;
    }

    template<class T>
    Sequence<std::string> *NaryTreeSerializer<T>::parse_serialized_children(const std::string &serialized_children) {
        auto* parsed_children = new LinkedListSequence<std::string>;
        std::string current_child;

        std::istringstream iss(serialized_children);

        char symbol; iss >> symbol;
        int depth = 1;
        while (depth > 0) {
            iss >> symbol;
            current_child += symbol;

            if (symbol == '(')
                depth++;
            else if (symbol == ')')
                depth--;

            if (depth == 1 && symbol == ')') {
                parsed_children->append(current_child);
                current_child.clear();
            }
        }

        return parsed_children;
    }

    template<class T>
    void NaryTreeSerializer<T>::append_parsed_children(NaryTree<T> *tree, const Sequence<std::string> *parsed_children, int max_children_data) {
        if (parsed_children->get_length() > max_children_data)
            throw IndexOutOfRangeException(
                    (int)parsed_children->get_length(), 0, max_children_data
            );

        for (int i = 0; i < parsed_children->get_length(); ++i) {
            NaryTree<T>* child_tree = deserialize_as_child(parsed_children->get(i), max_children_data);
            tree->add_child(child_tree);
            delete child_tree;
        }
    }

} // kogan

#endif //LAB4_NARY_TREE_SERIALIZER_HPP
