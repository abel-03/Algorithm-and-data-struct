#include <iostream>
#include <set>

struct Track {
  std::pair<int, int> pr;
  std::multiset<int> p;
  std::multiset<int> dist;
  std::multiset<std::pair<int, int>> y1;
  std::multiset<std::pair<int, int>> y2;
};
void Insert(Track* track, int n, int x);
void Print(std::multiset<int>::iterator it);
void Cmd(Track* track, int x);
void Clear(Track* track);
void Cam(Track* track, int y);

void Insert(Track* track, int n, int x) {
  int i = 0;
  int cp_x = 0;
  int cp_y1 = 0;
  int cp_y2 = 0;
  while (i < n) {
    std::cin >> cp_x >> cp_y1 >> cp_y2;
    track->pr.first = cp_y1;
    track->pr.second = cp_x;
    track->y1.insert(track->pr);
    track->pr.first = cp_y2;
    track->y2.insert(track->pr);
    i++;
  }
  Cmd(track, x);
}
void Cmd(Track* track, int x) {
  track->p.insert(0);
  track->p.insert(x);
  track->dist.insert(x);
}
void Print(std::multiset<int>::iterator it) { std::cout << *it << std::endl; }
void Clear(Track* track) { delete track; }
void Cam(Track* track, int y) {
  int i = 0;
  std::multiset<std::pair<int, int>>::iterator iter_y1 = track->y1.begin();
  std::multiset<std::pair<int, int>>::iterator iter_y2 = track->y2.begin();
  while (i <= y) {
    while (true) {
      if (iter_y1 == track->y1.end() || iter_y1->first > i) {
        break;
      }
      auto iter = track->p.insert(iter_y1->second);
      iter++;
      auto iter_one = iter;
      iter--;
      auto iter_two = iter;
      iter_two--;
      auto dist = track->dist.find(*iter_one - *iter_two);
      if (track->dist.end() != dist) {
        track->dist.erase(dist);
      }
      track->dist.insert(*iter_one - *iter);
      track->dist.insert(*iter - *iter_two);
      iter_y1++;
    }
    while (true) {
      if (iter_y2 == track->y2.end() || iter_y2->first >= i) {
        break;
      }
      auto iter = track->p.find(iter_y2->second);
      iter++;
      auto iter_one = iter;
      iter--;
      auto iter_two = iter;
      iter_two--;
      track->dist.insert(*iter_one - *iter_two);
      auto temp = track->dist.find(*iter_one - *iter);
      if (track->dist.end() != temp) {
        track->dist.erase(temp);
      }
      temp = track->dist.find(*iter - *iter_two);
      if (track->dist.end() != temp) {
        track->dist.erase(temp);
      }
      temp = track->p.find(iter_y2->second);
      if (track->p.end() != temp) {
        track->p.erase(temp);
      }
      iter_y2++;
    }
    std::multiset<int>::iterator it = track->dist.end();
    it--;
    Print(it);
    i++;
  }
}

int main() {
  Track* track = new Track;
  int n = 0;
  int x = 0;
  int y = 0;
  std::cin >> n >> y >> x;
  Insert(track, n, x);
  Cam(track, y);
  Clear(track);
  return 0;
}