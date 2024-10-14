#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>

using namespace std;

class JSONValue {
public:
    virtual ~JSONValue() = default;
    virtual bool compare(const JSONValue& other) const = 0;
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
        const JSONInteger* otherInt = dynamic_cast<const JSONInteger*>(&other);
        return otherInt && value == otherInt->value;
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
        const JSONString* otherStr = dynamic_cast<const JSONString*>(&other);
        return otherStr && value == otherStr->value;
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
        const JSONArray* otherArray = dynamic_cast<const JSONArray*>(&other);
        if (!otherArray || elements.size() != otherArray->elements.size()) {
            return false;
        }
        for (size_t i = 0; i < elements.size(); ++i) {
            if (!elements[i]->compare(*otherArray->elements[i])) {
                return false;
            }
        }
        return true;
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
        const JSONObject* otherObj = dynamic_cast<const JSONObject*>(&other);
        if (!otherObj || properties.size() != otherObj->properties.size()) {
            return false;
        }
        for (const auto& pair : properties) {
            auto it = otherObj->properties.find(pair.first);
            if (it == otherObj->properties.end() || !pair.second->compare(*it->second)) {
                return false;
            }
        }
        return true;
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
    JSONArray* array1 = new
JSONArray(arrayElements);
    
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