//
// Created by Gregory Kogan on 27.05.2023.
//

#ifndef LAB4_NARY_TREE_SERIALIZER_HPP
#define LAB4_NARY_TREE_SERIALIZER_HPP

#include "../../trees/nary_tree.hpp"


namespace kogan {

    template <class T> class NaryTreeSerializer {
        NaryTree<T>* tree;
        std::string serialized_tree;

        int max_children_data = std::numeric_limits<int>::max();

        void serialize();
        [[nodiscard]] std::string serialize_child(const NaryTree<T>* child);

        void deserialize();
        NaryTree<T>* deserialize_child(const std::string& serialized_child);
        T read_until_open_bracket(const std::string& str);
        std::string parse_content(const std::string& str);
        Sequence<std::string>* parse_serialized_children(const std::string& serialized_children);
        void append_parsed_children(NaryTree<T>* subtree, const Sequence<std::string>* parsed_children);

    public:
        explicit NaryTreeSerializer(const NaryTree<T>& tree);
        explicit NaryTreeSerializer(const std::string& serialized_tree);

        ~NaryTreeSerializer();

        [[nodiscard]] const NaryTree<T>* get_tree() const;
        [[nodiscard]] std::string get_serialized_tree() const;
    };

    template<class T>
    NaryTreeSerializer<T>::NaryTreeSerializer(const NaryTree<T> &tree) {
        this->tree = new NaryTree<T>(tree);
        serialize();
    }

    template<class T>
    NaryTreeSerializer<T>::NaryTreeSerializer(const std::string& serialized_tree) {
        this->serialized_tree = serialized_tree;
        deserialize();
    }

    template<class T>
    NaryTreeSerializer<T>::~NaryTreeSerializer() {
        delete tree;
    }

    template<class T>
    const NaryTree<T> *NaryTreeSerializer<T>::get_tree() const {
        return tree;
    }

    template<class T>
    std::string NaryTreeSerializer<T>::get_serialized_tree() const {
        return serialized_tree;
    }

    template<class T>
    void NaryTreeSerializer<T>::serialize() {
        std::ostringstream oss;
        oss << tree->max_children_count() << " ";
        oss << serialize_child(tree);
        serialized_tree = oss.str();
    }

    template<class T>
    std::string NaryTreeSerializer<T>::serialize_child(const NaryTree<T>* child) {
        std::ostringstream oss;
        oss << child->get_data();

        oss << "(";
        for (int i = 0; i < child->children_count(); ++i)
            oss << serialize_child(child->get_child(i));
        oss << ")";

        return oss.str();
    }

    template<class T>
    void NaryTreeSerializer<T>::deserialize() {
        std::istringstream iss(serialized_tree);
        iss >> max_children_data;
        if (max_children_data < 1)
            throw InvalidArgumentException("max_children");

        std::string remaining_string;
        getline(iss, remaining_string);
        this->tree = deserialize_child(remaining_string);
    }

    template<class T>
    NaryTree<T> *NaryTreeSerializer<T>::deserialize_child(const std::string &serialized_child) {
        T root_value = read_until_open_bracket(serialized_child);
        auto* result = new NaryTree<T>(root_value, max_children_data);

        Sequence<std::string>* parsed_children = parse_serialized_children(
                parse_content(serialized_child)
        );

        append_parsed_children(result, parsed_children);

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
    void NaryTreeSerializer<T>::append_parsed_children(NaryTree<T> *subtree, const Sequence<std::string> *parsed_children) {
        if (parsed_children->get_length() > max_children_data)
            throw IndexOutOfRangeException(
                    (int)parsed_children->get_length(), 0, max_children_data
            );

        for (int i = 0; i < parsed_children->get_length(); ++i) {
            NaryTree<T>* child_tree = deserialize_child(parsed_children->get(i));
            subtree->add_child(child_tree);
            delete child_tree;
        }
    }

} // kogan

#endif //LAB4_NARY_TREE_SERIALIZER_HPP
