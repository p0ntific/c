#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class JSONInteger;
class JSONString;
class JSONArray;
class JSONObject;

class JSONValueVisitor {
public:
    virtual bool visit(const JSONInteger& value) = 0;
    virtual bool visit(const JSONString& value) = 0;
    virtual bool visit(const JSONArray& value) = 0;
    virtual bool visit(const JSONObject& value) = 0;
    virtual ~JSONValueVisitor() = default;
};

class JSONValue {
public:
    virtual ~JSONValue() = default;
    virtual bool compare(const JSONValue& other) const = 0;
    virtual bool acceptVisitor(JSONValueVisitor& visitor) const = 0;
    virtual void print() const = 0;
};

class JSONInteger : public JSONValue {
    int value;

public:
    explicit JSONInteger(int v) : value(v) {}

    int getValue() const { 
        return value; 
    }

    bool compare(const JSONValue& other) const override {
        struct IntegerVisitor : JSONValueVisitor {
            const JSONInteger& instance;
            IntegerVisitor(const JSONInteger& instance) : instance(instance) {}
            bool visit(const JSONInteger& other) override { return instance.value == other.value; }
            bool visit(const JSONString&) override { return false; }
            bool visit(const JSONArray&) override { return false; }
            bool visit(const JSONObject&) override { return false; }
        } visitor(*this);
        return other.acceptVisitor(visitor);
    }

    bool acceptVisitor(JSONValueVisitor& visitor) const override {
        return visitor.visit(*this);
    }

    void print() const override {
        cout << value;
    }
};

class JSONString : public JSONValue {
    string value;

public:
    explicit JSONString(string s) : value(std::move(s)) {}

    string getValue() const { return value; }

    bool compare(const JSONValue& other) const override {
        struct StringVisitor : JSONValueVisitor {
            const JSONString& instance;
            StringVisitor(const JSONString& instance) : instance(instance) {}
            bool visit(const JSONInteger&) override { return false; }
            bool visit(const JSONString& other) override { return instance.value == other.value; }
            bool visit(const JSONArray&) override { return false; }
            bool visit(const JSONObject&) override { return false; }
        } visitor(*this);
        return other.acceptVisitor(visitor);
    }

    bool acceptVisitor(JSONValueVisitor& visitor) const override {
        return visitor.visit(*this);
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

    const vector<JSONValue*>& getElements() const { return elements; }

    bool compare(const JSONValue& other) const override {
        struct ArrayVisitor : JSONValueVisitor {
            const JSONArray& instance;
            ArrayVisitor(const JSONArray& instance) : instance(instance) {}
            bool visit(const JSONInteger&) override { return false; }
            bool visit(const JSONString&) override { return false; }
            bool visit(const JSONArray& other) override { 
                if (instance.elements.size() != other.elements.size()) return false;
                for (size_t i = 0; i < instance.elements.size(); ++i) {
                    if (!instance.elements[i]->compare(*other.elements[i])) return false;
                }
                return
true;
            }
            bool visit(const JSONObject&) override { return false; }
        } visitor(*this);
        return other.acceptVisitor(visitor);
    }

    bool acceptVisitor(JSONValueVisitor& visitor) const override {
        return visitor.visit(*this);
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

    const map<string, JSONValue*>& getProperties() const { return properties; }

    bool compare(const JSONValue& other) const override {
        struct ObjectVisitor : JSONValueVisitor {
            const JSONObject& instance;
            ObjectVisitor(const JSONObject& instance) : instance(instance) {}
            bool visit(const JSONInteger&) override { return false; }
            bool visit(const JSONString&) override { return false; }
            bool visit(const JSONArray&) override { return false; }
            bool visit(const JSONObject& other) override { 
                if (instance.properties.size() != other.properties.size()) return false;
                  for (const auto& pair : instance.properties) {
                        auto it = other.properties.find(pair.first);
                        if (it == other.properties.end() || !pair.second->compare(*it->second)) return false;
                    }
                return true;
            }
        } visitor(*this);
        return other.acceptVisitor(visitor);
    }

    bool acceptVisitor(JSONValueVisitor& visitor) const override {
        return visitor.visit(*this);
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