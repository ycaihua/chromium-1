// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELEROMETER_ACCELEROMETER_OBSERVER_H_
#define ASH_ACCELEROMETER_ACCELEROMETER_OBSERVER_H_

namespace gfx {
class Vector3dF;
}

namespace ash {

// The interface for classes which observe accelerometer updates.
class AccelerometerObserver {
 public:
  virtual void OnAccelerometerUpdated(const gfx::Vector3dF& base,
                                      const gfx::Vector3dF& lid) = 0;

 protected:
  virtual ~AccelerometerObserver() {}
};

}  // namespace ash

#endif  // ASH_ACCELEROMETER_ACCELEROMETER_OBSERVER_H_
