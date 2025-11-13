# include <map>
# include <iostream>

int main() {
    std::map<std::string, int> m {
	{ "Chris", 31 }, { "CS106L", 42 },
	{ "Keith", 14 }, { "Nick", 51 },
	{ "Sean", 35 },
};
    for (const auto& pair : m) {
	    std::cout << pair.first << " ";
	    std::cout << pair.second;
    }
}

