#pragma once
#include <ofColor.h>
#include <ofPoint.h>

#include <vector>

/**
 * @brief desktopgame
 * N次ベジェ曲線を描画するクラスです。
 * @see https://qiita.com/Rahariku/items/295b1062b77ed9c96d9c
 */
class ofxBezierCurve {
 public:
  explicit ofxBezierCurve();
  /**
   * @brief desktopgame
   * 任意の座標を含むコントロールポイントを選択状態にします。
   * 存在しなかった場合は新たにコントロールポイントを生成します。
   * @param x
   * @param y
   * @return int
   */
  int touch(float x, float y);
  /**
   * @brief desktopgame
   * 任意の座標を含むコントロールポイントが存在すれば選択状態にします。
   * @param x
   * @param y
   * @return int
   */
  int select(float x, float y);
  /**
   * @brief desktopgame
   * 任意の座標を含むコントロールポイントが存在すれば削除します。
   * @param x
   * @param y
   */
  void remove(float x, float y);
  /**
   * @brief desktopgame
   * 任意の座標を含むコントロールポイントを移動します。
   * @param x
   * @param y
   */
  void drag(float x, float y);
  /**
   * @brief desktopgame
   * コントロールポイントと、生成されたベジェ曲線を描画します。
   * @param step
   */
  void draw(float step);
  /**
   * @brief desktopgame
   * ある時間におけるベジェ曲線の座標を計算します。
   * @param t
   * @return ofPoint
   */
  ofPoint compute(float t) const;
  ofPoint compute(int index, float t) const;

 private:
  static int biCoe(int numPoints, int i);
  static int fact(int n);
  std::vector<ofPoint> m_points;
  int m_selectedIndex;
  float m_pointRadius;
  ofColor m_unselectColor;
  ofColor m_selectColor;
};