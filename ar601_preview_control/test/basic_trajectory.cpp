#include "basic_trajectory.h"

#include <cmath>

double basic_trajectory_t::x_os(double t)
{
  double x;
  if (t < t_preview + t0) {
    x = 0;
  } else
    x= floor((t - (t_preview + t0))/ t0) / 2.0 *l0 + 0.5*l0;
  return x;
}

double basic_trajectory_t::y_os(double t)
{
  double y;
  if (t < t_preview + t0) {
    y = -b_y0;
  } else if (floor((t - (t_preview + t0)) / t0) / 2.0 - floor(floor((t -
                (t_preview + t0)) / t0) / 2.0) == 0.0) {
    y = b_y0;
  } else {
    y = -b_y0;
  }

  return y;
}

double basic_trajectory_t::x_left(double t)
{
  double x;
  double k;
  if (t <= t_preview) {
    x = 0.0;
  } else {
    t -= t_preview;
    if (t <= p_ds * t0) {
      x = 0.0;
    } else if (t <= t0) {
      t -= p_ds * t0;
      x = 0.5 * l0 * 0.5 * (1.0 - cos(3.1415926535897931 * t / (t0 - p_ds * t0)));
    } else {
      k = floor((t - t0) / t0);
      t = (t - t0) - k * t0;
      if (k / 2.0 - floor(k / 2.0) == 0.0) {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }
      } else if (t <= p_ds * t0) {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        x -= 0.5 * l0;
      } else {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        x -= 0.5 * l0 * cos(1.0 / (t0 - p_ds * t0) * 3.1415926535897931 * (t -
          p_ds * t0));
      }
    }
  }

  return x;
}

double basic_trajectory_t::x_right(double t)
{
  double x;
  double k;
  if (t <= t_preview) {
    x = 0.0;
  } else {
    t -= t_preview;
    if (t <= p_ds * t0) {
      x = 0.0;
    } else if (t <= t0) {
      x = 0.0;
    } else {
      k = floor((t - t0) / t0);
      t = (t - t0) - k * t0;
      if (k / 2.0 - floor(k / 2.0) != 0.0) {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }
      } else if (t <= p_ds * t0) {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        x -= 0.5 * l0;
      } else {
        k = ((t + t0) + k * t0) + t_preview;

        /* UNTITLED Summary of this function goes here */
        /*    Detailed explanation goes here */
        if (k < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((k - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        x -= 0.5 * l0 * cos(1.0 / (t0 - p_ds * t0) * 3.1415926535897931 * (t -
          p_ds * t0));
      }
    }
  }

  return x;
}

double basic_trajectory_t::z_left(double t)
{
  double z;
  double k;
  if (t <= t_preview) {
    z = 0.0;
  } else {
    t -= t_preview;
    k = floor(t / t0);
    t -= k * t0;
    if (k / 2.0 - floor(k / 2.0) != 0.0) {
      z = 0.0;
    } else if (t <= p_ds * t0) {
      z = 0.0;
    } else {
      z = 0.5 * h * (1.0 - cos(2.0 * (1.0 / (t0 - p_ds * t0)) *
        3.1415926535897931 * (t - p_ds * t0)));
    }
  }

  return z;
}

double basic_trajectory_t::z_right(double t)
{
  double z;
  double k;
  if (t <= t_preview) {
    z = 0.0;
  } else {
    t -= t_preview;
    k = floor(t / t0);
    t -= k * t0;
    if (k / 2.0 - floor(k / 2.0) == 0.0) {
      z = 0.0;
    } else if (t <= p_ds * t0) {
      z = 0.0;
    } else {
      z = 0.5 * h * (1.0 - cos(2.0 * (1.0 / (t0 - p_ds * t0)) *
        3.1415926535897931 * (t - p_ds * t0)));
    }
  }

  return z;
}

double basic_trajectory_t::d_zmp_x(double t)
{
  double x;
  double k;
  double b_t;
  if (t <= t_preview) {
    x = 0.0;
  } else {
    t -= t_preview;
    k = floor(t / t0);
    t -= k * t0;
    if (t <= p_ds * t0) {
      if (k == 0.0) {
        b_t = t / (p_ds * t0);
        x = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * 0.0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * 0.02;
      } else {
        b_t = ((t + t_preview) + k * t0) - t0;
        if (b_t < t_preview + t0) {
          x = 0.0;
        } else {
          x = floor((b_t - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        b_t = (t + t_preview) + k * t0;
        if (b_t < t_preview + t0) {
          k = 0.0;
        } else {
          k = floor((b_t - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
        }

        b_t = t / (p_ds * t0);
        x = ((1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * x + b_t * b_t *
             (3.0 - 2.0 * b_t) * k) + 0.02;
      }
    } else {
      b_t = (t + k * t0) + t_preview;
      if (b_t < t_preview + t0) {
        x = 0.0;
      } else {
        x = floor((b_t - (t_preview + t0)) / t0) * 0.5 * l0 + 0.5 * l0;
      }

      x += 0.02;
    }
  }

  return x;
}

double basic_trajectory_t::d_zmp_y(double t)
{
  double y;
  double k;
  double b_t;
  double d_y0;
  if (t <= t_preview) {
    y = 0.0;
  } else {
    t -= t_preview;
    k = floor(t / t0);
    t -= k * t0;
    if (t <= p_ds * t0) {
      if (k == 0.0) {
        k = y_os((t + t_preview) + 0.0 * t0);
        b_t = t / (p_ds * t0);
        y = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * 0.0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * k;
      } else {
        d_y0 = y_os(((t + t_preview) + k * t0) - t0);
        k = y_os((t + t_preview) + k * t0);
        b_t = t / (p_ds * t0);
        y = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * d_y0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * k;
      }
    } else {
      y = y_os((t + k * t0) + t_preview);
    }
  }

  return y;
}

double basic_trajectory_t::d_zmp_y_2(double t)
{
  double y;
  int k;
  double b_fix;
  double b_y1;
  double b_t;
  double hoistedGlobal;
  double b_hoistedGlobal;
  double d_y0;
  double x;
  if (t <= t_preview) {
    y = 0.0;
  } else {
    t -= t_preview;
    k = floor(t / t0);
    t -= k * t0;
    if ((k%2) == 0) {
      b_fix = -d_x;
    } else {
      b_fix = d_x;
    }

    if (t <= p_ds * t0) {
      if (k == 0.0) {
        b_y1 = y_os((t + t_preview) + 0.0 * t0);
        b_t = t / (p_ds * t0);
        y = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * 0.0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * b_y1;
      } else {
        hoistedGlobal = t_preview;
        b_hoistedGlobal = t0;
        d_y0 = y_os(((t + t_preview) + k * t0) - t0);
        b_y1 = y_os((t + hoistedGlobal) + k * b_hoistedGlobal) + b_fix;
        b_t = t / (p_ds * t0);
        y = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * d_y0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * b_y1;
      }
    } else if (t <= p_ds * t0 + d_t) {
      if (k == 0.0) {
        y = y_os((t + 0.0 * t0) + t_preview);
      } else {
        hoistedGlobal = t0;
        b_hoistedGlobal = t_preview;
        x = t - p_ds * t0;
        d_y0 = y_os((t + t_preview) + k * t0) + b_fix;
        b_y1 = y_os((t + k * hoistedGlobal) + b_hoistedGlobal);
        b_t = x / d_t;
        y = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * d_y0 + b_t * b_t *
          (3.0 - 2.0 * b_t) * b_y1;
      }
    } else {
      y = y_os((t + k * t0) + t_preview);
    }
  }

  return y;
}

void basic_trajectory_t::fill_trajectories()
{
  l0 = 0.1;
  h = 0.03;
  t0 = 10;
  p_ds = 0.5;
  t_preview = 2.0;
  b_y0 = 0.088;
  d_x=0.03;
  d_t=1;
  double p = 1000;
  T = 4e-3;
  N = (p*t0 + 2*t_preview)/T;
  x_op = new double[N];
  y_op = new double[N];
  desired_zmp_x = new double[N];
  desired_zmp_y = new double[N];
  ax_left = new double[N];
  az_left = new double[N];
  ax_right = new double[N];
  az_right = new double[N];
  for (int i = 0; i < N; i++) {
    double t = i*T;
    x_op[i] = x_os(t);
    y_op[i] = y_os(t);
    ax_left[i] = x_left(t);
    az_left[i] = z_left(t);
    ax_right[i] = x_right(t);
    az_right[i] = z_right(t);
    desired_zmp_x[i] = d_zmp_x(t);
    desired_zmp_y[i] = d_zmp_y(t);
  }
}
