#include "LoginFilter.h"
#include "Utils/jwtService.h"

void LoginFilter::doFilter(const drogon::HttpRequestPtr &req,
                           drogon::FilterCallback &&fcb,
                           drogon::FilterChainCallback &&fccb) {
  std::optional<int> userId = JwtService::getCurrentUserIdFromRequest(req);
  if (userId.has_value()) {
    fccb();
    return;
  }

  auto res = drogon::HttpResponse::newHttpResponse();
  res->setStatusCode(drogon::k401Unauthorized);
  fcb(res);
}