#ifndef ARSLANTECH_JWTSERVICE_H
#define ARSLANTECH_JWTSERVICE_H

#include "../models/Users.h"
#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include <optional>
#include <string>

class JwtService {
public:
  static std::string
  generateFromUser(const drogon_model::realworld::Users &user);
  static std::optional<int> getUserIdFromJwt(const std::string &token);
  static std::optional<int>
  getCurrentUserIdFromRequest(const drogon::HttpRequestPtr &req);
  static void getCurrentUserFromRequest(
      const drogon::HttpRequestPtr &req,
      const std::function<void(std::optional<drogon_model::realworld::Users>)>
          &callback);

private:
  static const std::string secret;
  static const int duration;
  static const jwt::verifier<jwt::default_clock> verifier_;
};

#endif // ARSLANTECH_JWTSERVICE_H