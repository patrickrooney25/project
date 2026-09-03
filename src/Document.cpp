#include "Document.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

Document::Document(std::string title, std::string contents) : title_(std::move(title)), contents_(std::move(contents)) {

}

bool Document::operator==(const Document& other) const {
    if(title_==other.title_ && sourcePath_==other.sourcePath_&&contents_ ==other.contents_){
        return true;
    }
    return false;
}

bool Document::operator!=(const Document& other) const {
    if(title_!=other.title_ || sourcePath_ !=other.sourcePath_ || contents_!=other.contents_){
        return true;
    }
    return false;
}

bool Document::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()){
        return false;
    }
    std::stringstream buffer;
    buffer <<file.rdbuf();
    std::filesystem::path p(path);
    contents_= buffer.str();
    sourcePath_ =path;
    title_=p.filename().string();
    return true;
}

const std::string& Document::title() const noexcept {
    return title_;
}

const std::string& Document::sourcePath() const noexcept {
    return sourcePath_;
}

const std::string& Document::contents() const noexcept {
    return contents_;
}

void Document::setTitle(std::string title) {
    title_=std::move(title);
}

std::size_t Document::characterCount() const noexcept {
    return contents_.length();
}

bool Document::empty() const noexcept {
    return contents_.empty();
}
