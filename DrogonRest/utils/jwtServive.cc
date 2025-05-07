#include "jwtService.h"

const std::string JwtService::secret =
    drogon::app().getCustomConfig()["jwt-secret"].asString();
const int JwtService::duration =
    drogon::app().getCustomConfig()["jwt-sessionTime"].asInt();
const jwt::verifier<jwt::default_clock> JwtService::verifier_ =
    jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{JwtService::secret})
        .with_issuer("auth0");

std::string
JwtService::generateFromUser(const drogon_model::realworld::Users &user) {
  return jwt::create()
      .set_issuer("auth0")
      .set_type("JWS")
      .set_payload_claim("user",
                         jwt::claim(std::to_string(user.getValueOfId())))
      .sign(jwt::algorithm::hs256{secret});
}

std::optional<int> JwtService::getUserIdFromJwt(const std::string &token) {
  auto decoded = jwt::decode(token);
  try {
    verifier_.verify(decoded);
  } catch (const std::runtime_error &e) {
    drogon::LOG_ERROR << e.what();
    return std::nullopt;
  }
  return std::stoi(decoded.get_payload_claim("user").as_string());
}