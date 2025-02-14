#include AOC_HEADER

#include <iostream>
#include <sstream>
#include <utility>

#define MAX_SIDE 1000

struct Claim {
    int claim_id = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    Claim(std::string inp);
    friend std::ostream& operator<<(std::ostream& os, Claim& claim) {
        os << claim.claim_id << " | " << claim.x << ":" << claim.y << " " << claim.width << ":" << claim.height;
        return os;
    }
};

Claim::Claim(std::string inp) {
    std::stringstream ss(inp);
    char del = '\0';
    ss >> del >> claim_id >> del >> x >> del >> y >> del >> width >> del >> height;
}

struct Fabric {
    std::vector<std::vector<int>> fabric;
    std::pair<int, int> x_scope = {-1, -1};
    std::pair<int, int> y_scope = {-1, -1};
    Fabric() : fabric(std::vector(MAX_SIDE, std::vector(MAX_SIDE, 0))) {}
    void insert_claim(Claim& claim);
    int nr_of_overlaps();
    void print();
    int find_claim(std::vector<Claim> claims);
};

void Fabric::insert_claim(Claim& claim) {
    for (int y = claim.y; y < claim.y + claim.height; ++y) {
        for (int x = claim.x; x < claim.x + claim.width; ++x) {
            fabric.at(y).at(x)++;
        }
    }
    if (auto [min, max] = x_scope; min == -1) {
        x_scope = {claim.x, claim.x + claim.width};
        y_scope = {claim.y, claim.y + claim.height};
    }
    std::get<0>(x_scope) = std::min(std::get<0>(x_scope), claim.x);
    std::get<1>(x_scope) = std::max(std::get<1>(x_scope), claim.x + claim.width);
    std::get<0>(y_scope) = std::min(std::get<0>(y_scope), claim.y);
    std::get<1>(y_scope) = std::max(std::get<1>(y_scope), claim.y + claim.height);
}

int Fabric::nr_of_overlaps() {
    int count = 0;
    for (int y = std::get<0>(y_scope); y <= std::get<1>(y_scope); ++y) {
        for (int x = std::get<0>(y_scope); x <= std::get<1>(y_scope); ++x) {
            if (fabric.at(y).at(x) > 1) {
                ++count;
            }
        }
    }
    return count;
}

void Fabric::print() {
    std::cout << "checking scope: " << std::get<0>(x_scope) << "->" << std::get<1>(x_scope) << " | "
              << std::get<0>(y_scope) << "->" << std::get<1>(y_scope) << std::endl;
    for (int y = std::get<0>(y_scope); y <= std::get<1>(y_scope); ++y) {
        for (int x = std::get<0>(y_scope); x <= std::get<1>(y_scope); ++x) {
            if (fabric.at(y).at(x) == 0) {
                std::cout << ".";
                continue;
            }
            std::cout << fabric.at(y).at(x);
        }
        std::cout << std::endl;
    }
}

int Fabric::find_claim(std::vector<Claim> claims) {
    for (auto& claim : claims) {
        bool valid_claim = true;
        for (int y = claim.y; valid_claim && y < claim.y + claim.height; ++y) {
            for (int x = claim.x; valid_claim && x < claim.x + claim.width; ++x) {
                if (fabric.at(y).at(x) > 1) {
                    valid_claim = false;
                }
            }
        }
        if (valid_claim) {
            return claim.claim_id;
        }
    }
    return 0;
}

std::pair<int, int> solve(std::vector<std::string> claims) {
    Fabric fabric;
    std::vector<Claim> vclaims;
    for (auto& claim : claims) {
        Claim c(claim);
        fabric.insert_claim(c);
        vclaims.push_back(std::move(c));
    }
    return {fabric.nr_of_overlaps(), fabric.find_claim(vclaims)};
}
