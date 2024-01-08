#pragma once
#include <vector>
#include <string>
#include "Nekretnina.hpp"

std::vector<Nekretnina> prikazDostupnihNekretnina(const std::string& filterTip, double minCena, double maxCena, double minPovrsina, int minBrojSoba, const std::string& sortiranje, const std::string& kljucneReci);
