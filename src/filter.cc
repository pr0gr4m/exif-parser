#include "filter.hh"
#include <string>

bool Filter::instanceFlag = false;
Filter* Filter::instance = nullptr;

Filter::Filter()
    : latitudeMin_(LATITUDEMIN), latitudeMax_(LATITUDEMAX),
      longtitudeMin_(LONGTITUDEMIN), longtitudeMax_(LONGTITUDEMAX),
      vendor_(VENDORANY), model_(MODELANY),
      widthMin_(WIDTHMIN), widthMax_(WIDTHMAX),
      heightMin_(HEIGHTMIN), heightMax_(HEIGHTMAX),
      dateMin_(DATEMIN), dateMax_(DATEMAX),
      timeMin_(TIMEMIN), timeMax_(TIMEMAX)
{
}

Filter* Filter::getInstance()
{
    if (!instance) {
        instance = new Filter();
        instanceFlag = true;
    }
    return instance;
}

bool Filter::cmpFilter(easyexif::EXIFInfo &info)
{
    if (info.GeoLocation.Latitude < latitudeMin_ ||
            info.GeoLocation.Latitude > latitudeMax_)
        return false;
    if (info.GeoLocation.Longitude < longtitudeMin_ ||
            info.GeoLocation.Longitude > longtitudeMax_)
        return false;
    if (vendor_ != VENDORANY && !(vendor_.empty()) && vendor_ != info.Make)
        return false;
    if (model_ != MODELANY && !(model_.empty()) && model_ != info.Model)
        return false;
    if (info.ImageWidth < widthMin_ ||
            info.ImageWidth > widthMax_)
        return false;
    if (info.ImageHeight < heightMin_ ||
            info.ImageHeight > heightMax_)
        return false;

    if (info.DateTime.empty())
        return true;

    std::string date = info.DateTime.substr(0, 10);
    std::string time = info.DateTime.substr(11, 19);
    if (date < dateMin_ || date > dateMax_)
        return false;
    if (time < timeMin_ || time > timeMax_)
        return false;

    return true;
}

bool Filter::setFilter(std::string latitudeMin, std::string latitudeMax,
                       std::string longtitudeMin, std::string longtitudeMax,
                       std::string v, std::string m,
                       std::string widthMin, std::string widthMax,
                       std::string heightMin, std::string heightMax,
                       std::string dateMin, std::string dateMax,
                       std::string timeMin, std::string timeMax)
{
    if (!latitudeMin.empty()) {
        double m = std::stod(latitudeMin, nullptr);
        if (m < LATITUDEMIN || m > LATITUDEMAX)
            return false;
        latitudeMin_ = m;
    }

    if (!latitudeMax.empty()) {
        double m = std::stod(latitudeMin, nullptr);
        if (m < LATITUDEMIN || m > LATITUDEMAX)
            return false;
        latitudeMax_ = m;
    }

    if (!longtitudeMin.empty()) {
        double m = std::stod(longtitudeMin, nullptr);
        if (m < LONGTITUDEMIN || m > LONGTITUDEMAX)
            return false;
        longtitudeMin_ = m;
    }

    if (!longtitudeMax.empty()) {
        double m = std::stod(longtitudeMin, nullptr);
        if (m < LONGTITUDEMIN || m > LONGTITUDEMAX)
            return false;
        longtitudeMax_ = m;
    }

    if (!v.empty()) {
        vendor_ = v;
    }

    if (!m.empty()) {
        model_ = m;
    }

    if (!widthMin.empty()) {
        unsigned m = std::stoi(widthMin, nullptr);
        if (m > WIDTHMAX)
            return false;
        widthMin_ = m;
    }

    if (!widthMax.empty()) {
        unsigned m = std::stoi(widthMax, nullptr);
        if (m > WIDTHMAX)
            return false;
        widthMax_ = m;
    }

    if (!heightMin.empty()) {
        unsigned m = std::stoi(heightMin, nullptr);
        if (m > HEIGHTMAX)
            return false;
        heightMin_ = m;
    }

    if (!heightMax.empty()) {
        unsigned m = std::stoi(heightMax, nullptr);
        if (m > HEIGHTMAX)
            return false;
        heightMax_ = m;
    }

    if (!dateMin.empty()) {
        if (dateMin.size() != 8)
            return false;
        if (dateMin.at(2) != ':' || dateMin.at(5) != ':')
            return false;
        if (dateMin < DATEMIN || dateMin > DATEMAX)
            return false;
        dateMin_ = dateMin;
    }

    if (!dateMax.empty()) {
        if (dateMax.size() != 8)
            return false;
        if (dateMax.at(2) != ':' || dateMax.at(5) != ':')
            return false;
        if (dateMax < DATEMIN || dateMax > DATEMAX)
            return false;
        dateMax_ = dateMax;
    }

    if (!timeMin.empty()) {
        if (timeMin.size() != 10)
            return false;
        if (timeMin.at(4) != ':' || timeMin.at(7) != ':')
            return false;
        if (timeMin < TIMEMIN || timeMin > TIMEMAX)
            return false;
        timeMin_ = timeMin;
    }

    if (!timeMax.empty()) {
        if (timeMax.size() != 10)
            return false;
        if (timeMax.at(4) != ':' || timeMax.at(7) != ':')
            return false;
        if (timeMax < TIMEMIN || timeMax > TIMEMAX)
            return false;
        timeMax_ = timeMax;
    }

    return true;
}
