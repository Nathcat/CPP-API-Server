#include <api/api.hpp>
using namespace nathcat::api;

nathcat::api::Server::Server() {
  http.set_logger([](const httplib::Request &req,
                     const httplib::Response &res) {
    std::cout << req.method << " " << req.path << " -> " << res.status
              << std::endl;

    std::cout << "FORM DATA -----" << std::endl;
    for (auto i = req.form.fields.begin(); i != req.form.fields.end(); i++) {
      std::cout << i->first << " -> " << i->second.content << std::endl;
    }
    std::cout << "---------------" << std::endl;
  });
}

void nathcat::api::Server::registerEndpoint(struct endpoint e) {
  if (e.handlers.get != nullptr) {
    http.Get(e.path, e.handlers.get);
  }

  if (e.handlers.post != nullptr) {
    http.Post(e.path, e.handlers.post);
  }
}

void nathcat::api::Server::registerEndpoints(
    std::vector<struct endpoint> endpoints) {
  for (struct endpoint e : endpoints) {
    registerEndpoint(e);
  }
}
