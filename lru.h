#ifndef LRU_H__
#define LRU_H__

#include <map>
#include <list>
#include <mutex>

namespace {
constexpr unsigned int kMaxLen = 10000;
}

namespace yc {
template <typename K, typename V>
class LRUList {
public:
  LRUList(unsigned int max_len) : max_len_(max_len) {
    max_len_ = max_len_ > kMaxLen ? kMaxLen : max_len_;
  }
  ~LRUList() {}

  bool Get(K key, V& value) {
    std::unique_lock<std::mutex> lock(mutex_);
    auto res = m_.find(key);
    if (res == m_.end()) {
      return false;
    }
    l_.remove(key);
    l_.push_back(key);
    value = res->second;
    return true;
  }
  void Set(K key, V value) {
    std::unique_lock<std::mutex> lock(mutex_);
    auto res = m_.find(key);
    if (res != m_.end()) {
      l_.remove(key);
      l_.push_back(key);
      res->second = value;
      return;
    }
    if (m_.size() == max_len_) {
      auto tmp = l_.front();
      l_.pop_front();
      m_.erase(tmp);
    }
    m_[key] = value;
    l_.push_back(key);
  }

private:
  std::map<K, V> m_;
  std::list<K> l_;
  std::mutex mutex_;
  unsigned int max_len_;
};

}

#endif
