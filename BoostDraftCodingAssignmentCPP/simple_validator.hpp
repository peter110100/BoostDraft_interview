#ifndef SIMPLE_VALIDATOR_HPP
#define SIMPLE_VALIDATOR_HPP

#include <string>
#include <stack>
#include <cctype>
#include <iostream> // Include for error output

// Helper function to check if a tag name is valid
bool isValidTagName(const std::string& tag) {
    if (tag.empty()) return false;
    if (!isalpha(tag[0]) && tag[0] != '_') return false; // Tag must start with letter or underscore
    for (char ch : tag) {
        if (!(isalnum(ch) || ch == '_' || ch == ':')) return false;
    }
    return true;
}

// Helper function to parse a tag from the given position
std::string parseTag(const std::string& xml, size_t& pos) {
    std::string tag;
    while (pos < xml.size() && xml[pos] != '>') {
        tag += xml[pos++];
    }
    return tag;
}

// Main function to determine if the XML is valid
bool DetermineXml(const std::string &input) {
    std::stack<std::string> tags;
    size_t pos = 0;

    while (pos < input.size()) {
        if (input[pos] == '<') {
            pos++; // Move past '<'
            if (pos < input.size() && input[pos] == '/') { // Closing tag
                pos++; // Move past '/'
                std::string tag = parseTag(input, pos);
                if (tags.empty() || tags.top() != tag) {
                    return false;
                }
                tags.pop();
                if (pos < input.size() && input[pos] != '>') {
                    return false;
                }
                pos++; // Move past '>'
            } else { // Opening tag or self-closing tag
                if (pos < input.size() && input[pos] == '/') { // Self-closing tag
                    pos++; // Move past '/'
                    std::string tag = parseTag(input, pos);
                    if (!isValidTagName(tag)) {
                        return false;
                    }
                    if (input[pos] != '>') {
                        return false;
                    }
                    pos++; // Move past '>'
                } else { // Normal opening tag
                    std::string tag = parseTag(input, pos);
                    if (!isValidTagName(tag)) {
                        return false;
                    }
                    tags.push(tag);
                    if (pos < input.size() && input[pos] != '>') {
                        return false;
                    }
                    pos++; // Move past '>'
                }
            }
        } else {
            pos++; // Move to next character (ignoring text between tags)
        }
    }

    if (!tags.empty()) {
        return false;
    }

    return true; // Return true if all tags matched and stack is empty
}

#endif
