#pragma once

#include "token.hpp"

#include <optional>
#include <vector>

namespace hex::lang {

    class ASTNode {
    public:
        enum class Type {
            VariableDecl,
            TypeDecl,
            Struct,
            Scope,
        };

        explicit ASTNode(Type type) : m_type(type) {}
        virtual ~ASTNode() = default;

        Type getType() { return this->m_type; }

    private:
        Type m_type;
    };

    class ASTNodeVariableDecl : public ASTNode {
    public:
        explicit ASTNodeVariableDecl(const Token::TypeToken::Type &type, const std::string &name, const std::string& customTypeName = "", std::optional<u64> offset = { }, size_t arraySize = 1)
            : ASTNode(Type::VariableDecl), m_type(type), m_name(name), m_customTypeName(customTypeName), m_offset(offset), m_arraySize(arraySize) { }

        const Token::TypeToken::Type& getVariableType() const { return this->m_type; }
        const std::string& getCustomVariableTypeName() const { return this->m_customTypeName; }
        const std::string& getVariableName() const { return this->m_name; };
        std::optional<u64> getOffset() const { return this->m_offset; }
        size_t getArraySize() const { return this->m_arraySize; }

    private:
        Token::TypeToken::Type m_type;
        std::string m_name, m_customTypeName;
        std::optional<u64> m_offset;
        size_t m_arraySize;
    };

    class ASTNodeScope : public ASTNode {
    public:
        explicit ASTNodeScope(std::vector<ASTNode*> nodes) : ASTNode(Type::Scope), m_nodes(nodes) { }

        std::vector<ASTNode*> &getNodes() { return this->m_nodes; }
    private:
        std::vector<ASTNode*> m_nodes;
    };

    class ASTNodeStruct : public ASTNode {
    public:
        explicit ASTNodeStruct(std::string name, std::vector<ASTNode*> nodes)
            : ASTNode(Type::Struct), m_name(name), m_nodes(nodes) { }

        const std::string& getName() const { return this->m_name; }
        std::vector<ASTNode*> &getNodes() { return this->m_nodes; }
    private:
        std::string m_name;
        std::vector<ASTNode*> m_nodes;
    };

    class ASTNodeTypeDecl : public ASTNode {
    public:
        explicit ASTNodeTypeDecl(const Token::TypeToken::Type &type, const std::string &name, const std::string& customTypeName = "")
                : ASTNode(Type::TypeDecl), m_type(type), m_name(name), m_customTypeName(customTypeName) { }

        const std::string& getTypeName() const { return this->m_name; };

        const Token::TypeToken::Type& getAssignedType() const { return this->m_type; }
        const std::string& getAssignedCustomTypeName() const { return this->m_customTypeName; }
    private:
        Token::TypeToken::Type m_type;
        std::string m_name, m_customTypeName;
    };

}