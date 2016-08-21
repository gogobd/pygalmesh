#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <memory>
#include <vector>

#include "primitives.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

class DomainBase
{
  public:
  virtual std::vector<std::shared_ptr<loom::PrimitiveBase>> get_primitives() const = 0;
  virtual std::vector<std::vector<CGAL::Sign>> get_signs() const = 0;
};

class Ball: public DomainBase
{
  public:
    Ball(
        const std::vector<double> & x0,
        const double radius
        ):
      b_(std::make_shared<loom::BallPrimitive>(x0, radius))
    {
    }

    virtual std::vector<std::shared_ptr<loom::PrimitiveBase>> get_primitives() const
    {
      return {b_};
    }

    virtual std::vector<std::vector<CGAL::Sign>> get_signs() const {
      return {{b_->get_inside_sign()}};
    }

  private:
    const std::shared_ptr<loom::BallPrimitive> b_;
};


class Cuboid: public DomainBase
{
  public:
    Cuboid(
        const std::vector<double> & x0,
        const std::vector<double> & x1
        ):
      c_(std::make_shared<loom::CuboidPrimitive>(x0, x1))
    {
    }

    virtual std::vector<std::shared_ptr<loom::PrimitiveBase>> get_primitives() const
    {
      return {c_};
    }

    virtual std::vector<std::vector<CGAL::Sign>> get_signs() const {
      return {{c_->get_inside_sign()}};
    }

  private:
    const std::shared_ptr<loom::CuboidPrimitive> c_;
};


class Ellipsoid: public DomainBase
{
  public:
    Ellipsoid(
        const std::vector<double> & x0,
        const double a0,
        const double a1,
        const double a2
        ):
      e_(std::make_shared<loom::EllipsoidPrimitive>(x0, a0, a1, a2))
    {
    }

    virtual std::vector<std::shared_ptr<loom::PrimitiveBase>> get_primitives() const
    {
      return {e_};
    }

    virtual std::vector<std::vector<CGAL::Sign>> get_signs() const {
      return {{e_->get_inside_sign()}};
    }

  private:
    const std::shared_ptr<loom::EllipsoidPrimitive> e_;
};


void generate_mesh(
    const std::shared_ptr<DomainBase> & in,
    const bool lloyd = false,
    const bool odt = false,
    const bool perturb = true,
    const bool exude = true
    );
