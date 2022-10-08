#include <iostream>
#include <cmath>
#include <memory>
#include <stdlib.h>
#include <math.h>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;


const double pi = M_PI;

int vec_count=0;
class Vec3D {
public:
	const double x;
	const double y;
	const double z;

	Vec3D() : x{0}, y{0}, z{0} {
        cout << "Vec3D construct ("  << x << " " << y << " " << z << ") addr " << &x << endl;
        ++vec_count;
	}

	Vec3D(double x_in,double y_in, double z_in) : x{x_in}, y{y_in}, z{z_in} {
        cout << "Vec3D construct ("  << x << " " << y << " " << z << ") addr " << &x << endl;
        ++vec_count;
	}

    Vec3D(const Vec3D& v) : x{v.x}, y{v.y}, z{v.z} {
        cout << "Vec3D copy ("  << x << " " << y << " " << z << ") addr " << &x << endl;
        ++vec_count;
    }

    ~Vec3D() {
        cout << "Vec3D desruct ("  << x << " " << y << " " << z << ") addr " << &x << endl;
        --vec_count;
    }
    
    void operator=(const Vec3D &v) {
        cout << "Vec3D = ("  << x << " " << y << " " << z << ") addr " << &x << endl;
    }

    
	Vec3D sub(const Vec3D &other) const {
	    Vec3D res{x - other.x, y - other.y, z - other.z};
	    Vec3D neg{other.x - x, other.y - y, other.z - z};
	    if(x > other.x) {
		    return res;
	    } else {
		    return neg;
	    }
	}

	double dot(const Vec3D* v) const {
		return x * v->x + y * v->y + z * v->z;
	}

	Vec3D cross(const Vec3D v) const {
		Vec3D res(y * v.z - z * v.y,
		            z * v.x - x * v.z,
            		x * v.y - y * v.x);
        return res;
	}
	
	double lensq() const {
		return x*x + y*y + z*z;
	}
};

class Line {
    const Vec3D &u;
    const Vec3D &v;
    
public:
    Line(const Vec3D &ui, const Vec3D &vi) : u{ui}, v{vi} {}
    
    ~Line() {
        cout << "Line destruct\n";
    }
    
    double len() const {
        Vec3D w = u.sub(v);
        return sqrt(w.lensq());
    }
};

void heron() {
    Vec3D u{1,0,0};
    Vec3D v{0,1,0};
    Vec3D w{0,0,1};

    Line l1(u, v);
    double a = l1.len();
    Line l2(v, w);
    double b = l2.len();
    Line l3(w, u);
    double c = l3.len();
    cout << "Num vec " << vec_count << endl;
    double s = (a+b+c)/2;
    cout << "a " << a << " s " << s << " heron " << sqrt(s*(s-a)*(s-b)*(s-c)) << endl;
}


int main(int argc, char* argv[]) {
	double r = 1.0;
    int n_th = 20;
    int n_phi = 20;
    if(argc==4) {
        r = atof(argv[1]);
        n_th = atoi(argv[2]);
        n_phi = atoi(argv[3]);
    }

    heron();
    cout << "Num vec " << vec_count << endl;
}
