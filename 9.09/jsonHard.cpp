#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class JSONInteger;
class JSONString;
class JSONArray;
class JSONObject;

class IJSONVisitor {
public:
    virtual void visit(const JSONInteger&) = 0; 
    virtual void visit(const JSONString&) = 0; 
    virtual void visit(const JSONArray&) = 0;
    virtual void visit(const JSONObject&) = 0;
    virtual ~IJSONVisitor() = default;
};

class JSONValue {
public:
    virtual ~JSONValue() = default;
    virtual bool compare(const JSONValue& other) const = 0;
    virtual void accept(IJSONVisitor& visitor) const = 0;
    virtual void print() const = 0;
};

class JSONInteger : public JSONValue {
    int value;

public:
    explicit JSONInteger(int v) : value(v) {}

    bool compare(const JSONValue& other) const override {
        struct Visitor : IJSONVisitor {
            const JSONInteger& self;
            mutable bool result{false}; 
            Visitor(const JSONInteger& self) : self(self) {}

            void visit(const JSONInteger& other) override {
                result = self.value == other.value;
            }
            void visit(const JSONString&) override {}
            void visit(const JSONArray&) override {}
            void visit(const JSONObject&) override {}
        } visitor(*this);
        other.accept(visitor);
        return visitor.result;
    }

    void accept(IJSONVisitor& visitor) const override {
        visitor.visit(*this);
    }

    void print() const override {
        cout << value;
    }
};

class JSONString : public JSONValue {
    string value;

public:
    explicit JSONString(string s) : value(std::move(s)) {}

    bool compare(const JSONValue& other) const override {
        struct Visitor : IJSONVisitor {
            const JSONString& self;
            mutable bool result{false}; 
            Visitor(const JSONString& self) : self(self) {}

            void visit(const JSONString& other) override {  
                result = self.value == other.value;
            }
            void visit(const JSONInteger&) override {}
            void visit(const JSONArray&) override {}
            void visit(const JSONObject&) override {}
        } visitor(*this);
        other.accept(visitor);
        return visitor.result;
    }

    void accept(IJSONVisitor& visitor) const override {
        visitor.visit(*this);
    }

    void print() const override {
        cout << "\"" << value << "\"";
    }
};

class JSONArray : public JSONValue {
    vector<JSONValue*> elements;

public:
    explicit JSONArray(vector<JSONValue*> elems) : elements(std::move(elems)) {}

    ~JSONArray() {
        for (auto* elem : elements) {
            delete elem;
        }
    }

    bool compare(const JSONValue& other) const override {
        struct Visitor : IJSONVisitor {
            const JSONArray& self;
            mutable bool result{false};  
            Visitor(const JSONArray& self) : self(self) {}

            void visit(const JSONArray& other) override {  
                if (self.elements.size() != other.elements.size()) return;
                result = true;
                for (size_t i = 0; i < self.elements.size(); ++i) {
                    if (!self.elements[i]->compare(*other.elements[i])) {
                        result = false;
                        break;
                    }
                }
            }
            void visit(const JSONInteger&) override {}
            void visit(const JSONString&) override {}
            void visit(const JSONObject&) override {}
        } visitor(*this);
        other.accept(visitor);
        return visitor.result;
    }

    void accept(IJSONVisitor& visitor) const override {
        visitor.visit(*this);
    }

    void print() const override {
        cout << "[";
        for (size_t i = 0; i < elements.size(); ++i) {
            elements[i]->print();
            if (i < elements.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
    }
};

class JSONObject : public JSONValue {
    map<string, JSONValue*> properties;

public:
    explicit JSONObject(map<string, JSONValue*> props) : properties(std::move(props)) {}

    ~JSONObject() {
        for (auto& pair : properties) {
            delete pair.second;
        }
    }

    bool compare(const JSONValue& other) const override {
        struct Visitor : IJSONVisitor {
            const JSONObject& self;
            mutable bool result{false}; 
            Visitor(const JSONObject& self) : self(self) {}

            void visit(const JSONObject& other) override {
                if (self.properties.size() != other.properties.size()) return;
                result = true;
                for (const auto& pair : self.properties) {
                    auto it = other.properties.find(pair.first);
                    if (it == other.properties.end() || !pair.second->compare(*it->second)) {
                        result = false;
                        break;
                    }
                }
            }
            void visit(const JSONInteger&) override {}
            void visit(const JSONString&) override {}
            void visit(const JSONArray&) override {}
        } visitor(*this);
        other.accept(visitor);
        return visitor.result;
    }

    void accept(IJSONVisitor& visitor) const override {
        visitor.visit(*this);
    }

    void print() const override {
        cout << "{";
        auto it = properties.begin();
        while (it != properties.end()) {
            cout << "\"" << it->first << "\": ";
            it->second->print();
            if (++it != properties.end()) {
                cout << ", ";
            }
        }
        cout << "}";
    }
};

int main() {
    JSONInteger* integer1 = new JSONInteger(42);
    JSONInteger* integer2 = new JSONInteger(42);
    
    vector<JSONValue*> arrayElements = {integer1, new JSONString("test")};
    JSONArray* array1 = new JSONArray(arrayElements);
    
    map<string, JSONValue*> objProperties = {{"key1", integer1}, {"key2", array1}};
    JSONObject* object1 = new JSONObject(objProperties);

    cout << "Comparing integer1 and integer2: " << integer1->compare(*integer2) << endl;
    integer1->print();
    cout << endl;
    object1->print();
    cout << endl;

    delete integer2;

    delete object1;

    return 0;
}