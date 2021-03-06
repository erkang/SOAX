/**
 * Copyright (c) 2015, Lehigh University
 * All rights reserved.
 * See COPYING for license.
 *
 * This file defines the SOAC tip set class for the network configuration
 * procedure in SOAX.
 */

#ifndef SNAKE_TIP_SET_H_
#define SNAKE_TIP_SET_H_

#include <list>
#include <vector>
#include "./snake_tip.h"
#include "./global.h"

namespace soax {

class SnakeTipSet {
 public:
  typedef std::list<SnakeTip *> TipList;
  typedef std::vector<SnakeTip *> TipContainer;

  explicit SnakeTipSet(SnakeTip *t);

  /*
   * Get the average position of the tips in the set.
   */
  PointType position() const {return position_;}

  unsigned GetDegree() const {return degree_;}

  void Configure();

  void Add(SnakeTip *t);

  void Combine(SnakeTipSet *ts);

  /*
   * Returns the smallest distance from a tip in tips_ to t.
   */
  double ComputeDistance(SnakeTip *t) const;

  /*
   * Update the position of this snake tip set. The position is the
   * average point of all the snake tips in the set. This method needs
   * to be called in constructor and when new tips are added.
   */
  void UpdatePosition();

  void PrintSelf() const;

  void Purge(TipContainer &tips);

 private:
  double FindSmoothestPair(SnakeTip * &t1, SnakeTip * &t2);
  double ComputeTotalDistanceToOthers(SnakeTip *t) const;


  TipList tips_;
  PointType position_;
  unsigned degree_;

  DISALLOW_COPY_AND_ASSIGN(SnakeTipSet);
};

}  // namespace soax
#endif  // SNAKE_TIP_SET_H_
