
namespace frc {
/**
 * A change in distance along arc since the last pose update. We can use ideas
 * from differential calculus to create new Pose2ds from a Twist2d and vise
 * versa.
 *
 * A Twist can be used to represent a difference between two poses.
 */
struct Twist2d {
  /**
   * Linear "dx" component
   */
  okapi::meter dx = 0_m;

  /**
   * Linear "dy" component
   */
  okapi::meter dy = 0_m;

  /**
   * Angular "dtheta" component (radians)
   */
  okapi::radian dtheta = 0_rad;

  /**
   * Checks equality between this Twist2d and another object.
   *
   * @param other The other object.
   * @return Whether the two objects are equal.
   */
  bool operator==(const Twist2d& other) const {
    return (dx - other.dx).abs() < 1E-9_m &&
           (dy - other.dy).abs() < 1E-9_m &&
           (dtheta - other.dtheta).abs() < 1E-9_rad;
  }

  /**
   * Checks inequality between this Twist2d and another object.
   *
   * @param other The other object.
   * @return Whether the two objects are not equal.
   */
  bool operator!=(const Twist2d& other) const { return !operator==(other); }
};
}  // namespace frc
