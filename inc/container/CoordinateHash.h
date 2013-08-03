#ifndef COORDINATEHASH_H
#define COORDINATEHASH_H

#include <SFML/System.hpp>

class CoordinateHash{
    public:
        size_t operator()(const sf::Vector2i &k) const{
            return k.x * 60 + k.y;
        }
};

struct CoordinateEquals : std::binary_function<const sf::Vector2i&, const sf::Vector2i&, bool> {
      result_type operator()( first_argument_type lhs, second_argument_type rhs ) const
      {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
      }
};
#endif
