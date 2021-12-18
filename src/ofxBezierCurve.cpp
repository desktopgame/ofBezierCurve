#include "ofxBezierCurve.h"

#include <ofGraphics.h>
#include <ofMath.h>

#include <stdexcept>

ofxBezierCurve::ofxBezierCurve()
    : m_points(),
      m_selectedIndex(-1),
      m_pointRadius(10.0f),
      m_unselectColor(ofColor::white),
      m_selectColor(ofColor::red) {}

int ofxBezierCurve::touch(float x, float y) {
  this->m_selectedIndex = -1;
  select(x, y);
  if (this->m_selectedIndex == -1) {
    m_points.emplace_back(ofPoint(x, y));
  }
}

int ofxBezierCurve::select(float x, float y) {
  auto iter = m_points.begin();
  while (iter != m_points.end()) {
    const auto& e = *iter;
    float a = e.x;
    float b = e.y;
    bool contains = ((x - a) * (x - a)) + ((y - b) * (y - b)) <=
                    (m_pointRadius * m_pointRadius);
    if (contains) {
      this->m_selectedIndex = iter - m_points.begin();
      break;
    }
    ++iter;
  }
  return m_selectedIndex;
}

void ofxBezierCurve::remove(float x, float y) {
  this->m_selectedIndex = -1;
  select(x, y);
  if (this->m_selectedIndex != -1) {
    m_points.erase(m_points.begin() + m_selectedIndex);
    this->m_selectedIndex = -1;
  }
}

void ofxBezierCurve::drag(float x, float y) {
  if (this->m_selectedIndex == -1) {
    return;
  }
  auto& p = this->m_points[m_selectedIndex];
  p.x = x;
  p.y = y;
}

void ofxBezierCurve::draw(float step) {
  if (step >= 1.0f) {
    throw std::invalid_argument("step should be smaller than one.");
  }
  auto iter = m_points.begin();
  while (iter != m_points.end()) {
    const auto& e = *iter;
    int index = static_cast<int>(iter - m_points.begin());
    ofSetColor(index == m_selectedIndex ? m_selectColor : m_unselectColor);
    ofNoFill();
    ofDrawCircle(e, m_pointRadius);
    ofDrawBitmapString(std::to_string(index),
                       e + ofPoint(m_pointRadius, m_pointRadius));
    ++iter;
    if (iter != m_points.end()) {
      ofSetColor(ofColor::white);
      ofDrawLine(e, *iter);
    }
  }
  // ベジェ曲線の描画
  ofFill();
  ofSetColor(ofColor::blue);
  float t = 0.0f;
  while (t < 1.0f) {
    auto p = compute(t);
    ofDrawCircle(p, m_pointRadius / 2.0f);
    t = std::min(t + step, 1.0f);
  }
}

ofPoint ofxBezierCurve::compute(float t) const {
  ofPoint ret;
  for (int i = 0; i < static_cast<int>(m_points.size()); i++) {
    ofPoint a = compute(i, t);
    ret.x += a.x;
    ret.y += a.y;
  }
  return ret;
}

ofPoint ofxBezierCurve::compute(int index, float t) const {
  int numPoints = static_cast<int>(m_points.size()) - 1;
  float numPointsF = static_cast<float>(numPoints);
  float indexF = static_cast<float>(index);
  float scale = static_cast<float>(biCoe(numPoints, index)) *
                std::powf((1.0f - t), (numPointsF - indexF)) *
                std::powf(t, indexF);
  return m_points[index] * scale;
}

// private
int ofxBezierCurve::biCoe(int numPoints, int i) {
  if (numPoints < i) {
    return -1;
  }
  return fact(numPoints) / (fact(i) * fact(numPoints - i));
}

int ofxBezierCurve::fact(int n) {
  if (n <= 1) {
    return 1;
  }
  return n * fact(n - 1);
}