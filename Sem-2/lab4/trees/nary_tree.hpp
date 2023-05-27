//
// Created by Gregory Kogan on 21.05.2023.
//

#ifndef LAB4_NARY_TREE_HPP
#define LAB4_NARY_TREE_HPP

#include <limits>
#include <sequences/ArraySequence.hpp>
#include <containers/stack/stack.hpp>


namespace kogan {

    template <class T> class NaryTree {
        T data;
        int max_children;
        Sequence<NaryTree<T>*>* children;

        Sequence<T>* traverse_root_left_right() const;
        Sequence<T>* traverse_root_right_left() const;
        Sequence<T>* traverse_left_right_root() const;
        Sequence<T>* traverse_right_left_root() const;

        [[nodiscard]] std::string serialize_as_child() const;
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
        enum TraverseType {
            ROOT_LEFT_RIGHT,
            ROOT_RIGHT_LEFT,
            LEFT_RIGHT_ROOT,
            RIGHT_LEFT_ROOT,
        };

    public:
        NaryTree(T root_value, int max_children);
        explicit NaryTree(T root_value);

        ~NaryTree();

        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t children_count() const;
        [[nodiscard]] size_t max_children_count() const;
        [[nodiscard]] size_t height() const;
        T get_data() const;
        void set_data(T new_data);

        void add_child(T child);
        NaryTree<T>* get_child(int index) const;

        Sequence<T>* traverse() const;
        Sequence<T>* traverse(TraverseType traverse_type) const;

        [[nodiscard]] std::string to_string() const;
        [[nodiscard]] std::string to_string(TraverseType traverse_type) const;
        [[nodiscard]] std::string serialize() const;
        static NaryTree<T>* deserialize(const std::string& serialized_tree);

        NaryTree<T>* map(T (*func)(T)) const;

        NaryTree<T>& operator[](int index);
    };

    template<class T>
    NaryTree<T>::NaryTree(T root_value): NaryTree(root_value, std::numeric_limits<int>::max()) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

    template<class T>
    NaryTree<T>::NaryTree(T root_value, int max_children): max_children(max_children) {
        if (max_children < 1)
            throw InvalidArgumentException("max_children");

        children = new LinkedListSequence<NaryTree<T>*>;
        data = root_value;
    }

    template<class T>
    NaryTree<T>::~NaryTree() {
        for (int i = 0; i < children->get_length(); ++i)
            delete children->get(i);
        delete children;
    }

    template<class T>
    size_t NaryTree<T>::size() const {
        size_t result = 1;
        for (int i = 0; i < children->get_length(); ++i)
            result += children->get(i)->size();
        return result;
    }

    template<class T>
    size_t NaryTree<T>::children_count() const {
        return children->get_length();
    }

    template<class T>
    size_t NaryTree<T>::max_children_count() const {
        return (size_t)max_children;
    }

    template<class T>
    size_t NaryTree<T>::height() const {
        if (children->get_length() == 0)
            return 1;

        size_t max_child_height = 0;
        for (int i = 0; i < children_count(); ++i) {
            size_t child_height = get_child(i)->height();
            if (child_height > max_child_height)
                max_child_height = child_height;
        }

        return max_child_height + 1;
    }

    template<class T>
    T NaryTree<T>::get_data() const {
        return data;
    }

    template<class T>
    void NaryTree<T>::set_data(T new_data) {
        data = new_data;
    }

    template<class T>
    void NaryTree<T>::add_child(T child) {
        if (children->get_length() == max_children)
            throw kogan::IndexOutOfRangeException(max_children + 1, 0, max_children);

        children->append(new NaryTree<T>(child, max_children));
    }

    template<class T>
    NaryTree<T>* NaryTree<T>::get_child(int index) const {
        return children->get(index);
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse() const {
        return traverse(ROOT_LEFT_RIGHT);
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse(NaryTree::TraverseType traverse_type) const {
        switch (traverse_type) {
            case ROOT_LEFT_RIGHT:
                return traverse_root_left_right();
            case ROOT_RIGHT_LEFT:
                return traverse_root_right_left();
            case LEFT_RIGHT_ROOT:
                return traverse_left_right_root();
            case RIGHT_LEFT_ROOT:
                return traverse_right_left_root();
            default:
                throw InvalidArgumentException("traverse_type");
        }
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_root_left_right() const {
        Sequence<T>* result = new LinkedListSequence<T>;
        Stack<const NaryTree<T>*> stack;
        stack.push(this);

        while (!stack.empty()) {
            const NaryTree<T>* current = stack.pop();
            result->append(current->get_data());

            for (int i = current->children_count() - 1; i >= 0; --i)
                stack.push(current->get_child(i));
        }

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_root_right_left() const {
        Sequence<T>* result = new LinkedListSequence<T>;
        Stack<const NaryTree<T>*> stack;
        stack.push(this);

        while (!stack.empty()) {
            const NaryTree<T>* current = stack.pop();
            result->append(current->get_data());

            for (int i = 0; i < current->children_count(); ++i)
                stack.push(current->get_child(i));
        }

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_left_right_root() const {
        Sequence<T>* result = new LinkedListSequence<T>;

        if (children_count() == 0) {
            result->append(get_data());
            return result;
        }

        for (int i = 0; i < children_count(); ++i) {
            Sequence<T> *child_traverse = get_child(i)->traverse_left_right_root();
            Sequence<T>* concatenation = result->concat(child_traverse);
            delete result;
            result = concatenation;
        }
        result->append(get_data());

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_right_left_root() const {
        Sequence<T>* result = new LinkedListSequence<T>;

        if (children_count() == 0) {
            result->append(get_data());
            return result;
        }

        for (int i = children_count() - 1; i >= 0; --i) {
            Sequence<T> *child_traverse = get_child(i)->traverse_right_left_root();
            Sequence<T>* concatenation = result->concat(child_traverse);
            delete result;
            result = concatenation;
        }
        result->append(get_data());

        return result;
    }

    template<class T>
    std::string NaryTree<T>::to_string() const {
        Sequence<T>* path = traverse();
        std::string result = path->to_string();
        delete path;
        return result;
    }

    template<class T>
    std::string NaryTree<T>::to_string(NaryTree::TraverseType traverse_type) const {
        Sequence<T>* path = traverse(traverse_type);
        std::string result = path->to_string();
        delete path;
        return result;
    }

    template<class T>
    std::string NaryTree<T>::serialize() const {
        std::ostringstream oss;
        oss << max_children << " ";
        oss << serialize_as_child();
        return oss.str();
    }

    template<class T>
    std::string NaryTree<T>::serialize_as_child() const {
        std::ostringstream oss;
        oss << get_data();

        oss << "(";
        for (int i = 0; i < children_count(); ++i)
            oss << get_child(i)->serialize_as_child();
        oss << ")";

        return oss.str();
    }

    template<class T>
    NaryTree<T> *NaryTree<T>::deserialize(const std::string& serialized_tree) {
        std::istringstream iss(serialized_tree);
        int max_children_data; iss >> max_children_data;
        if (max_children_data < 1)
            throw InvalidArgumentException("max_children");

        std::string remaining_string;
        getline(iss, remaining_string);
        return deserialize_as_child(remaining_string, max_children_data);
    }

    template<class T>
    NaryTree<T> *NaryTree<T>::deserialize_as_child(const std::string &serialized_tree, int max_children_data) {
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
    T NaryTree<T>::read_until_open_bracket(const std::string &str) {
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
    std::string NaryTree<T>::parse_content(const std::string &str) {
        std::string content;
        size_t first_open_bracket_index = str.find('(');
        size_t last_close_bracket_index = str.rfind(')');
        for (size_t i = first_open_bracket_index; i <= last_close_bracket_index; ++i)
            content += str[i];
        return content;
    }

    template<class T>
    Sequence<std::string> *NaryTree<T>::parse_serialized_children(const std::string &serialized_children) {
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
    void NaryTree<T>::append_parsed_children(NaryTree<T> *tree, const Sequence<std::string> *parsed_children, int max_children_data) {
        if (parsed_children->get_length() > max_children_data)
            throw IndexOutOfRangeException(
                    (int)parsed_children->get_length(), 0, max_children_data
            );

        for (int i = 0; i < parsed_children->get_length(); ++i)
            tree->children->append(
                    deserialize_as_child(parsed_children->get(i), max_children_data)
            );
    }

    template<class T>
    NaryTree<T> *NaryTree<T>::map(T (*func)(T)) const {
        auto* result = new NaryTree<T>(*this);

        Stack<NaryTree<T>*> stack;
        stack.push(result);

        while (!stack.empty()) {
            NaryTree<T>* current = stack.pop();
            current->set_data(func(current->get_data()));

            for (int i = 0; i < current->children_count(); ++i)
                stack.push(current->get_child(i));
        }

        return result;
    }

    template<class T>
    NaryTree<T>& NaryTree<T>::operator[](int index) {
        return *(children->operator[](index));
    }

} // kogan

#endif //LAB4_NARY_TREE_HPP
