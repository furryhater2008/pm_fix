#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))

namespace Math {
	float ToDegrees(float radians) {
		return (radians * (180.f / PI));
	}
	void Normalize(float& Yaw, float& Pitch) {
		if (Pitch < -89) Pitch = -89;
		else if (Pitch > 89) Pitch = 89;
		if (Yaw < -360) Yaw += 360;
		else if (Yaw > 360) Yaw -= 360;
	}
	float NormalizeAngle(float angle) {
		while (angle > 360.0f) {
			angle -= 360.0f;
		}
		while (angle < 0.0f) {
			angle += 360.0f;
		}
		return angle;
	}

	Vector2 NormalizeAngles(Vector2 angles) {
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		return angles;
	}
	float BOG_TO_GRD(float BOG) {
		return (180 / M_PI) * BOG;
	}
	float GRD_TO_BOG(float GRD) {
		return (M_PI / 180) * GRD;
	}
	float Distance_3D(Vector3 a, Vector3 b) {
		return sqrtf(powf((a.x - b.x), 2) + powf((a.y - b.y), 2) + powf((a.z - b.z), 2));
	}
	float Distance_2D(Vector2 a, Vector2 b) {
		return sqrt(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
	}
	Vector3 NormalizeAngles(Vector3 angles) {
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);
		return angles;
	}
	Vector3 EulerAngles(Quaternion q1) {
		float num = q1.w * q1.w;
		float num2 = q1.x * q1.x;
		float num3 = q1.y * q1.y;
		float num4 = q1.z * q1.z;
		float num5 = num2 + num3 + num4 + num;
		float num6 = q1.x * q1.w - q1.y * q1.z;
		Vector3 vector;
		if (num6 > 0.4995f * num5) {
			vector.y = 2.0f * std::atan2f(q1.y, q1.x);
			vector.x = 1.57079637f;
			vector.z = 0.0f;
			return NormalizeAngles(vector * 57.2958f);
		}
		if (num6 < -0.4995f * num5) {
			vector.y = -2.0f * std::atan2f(q1.y, q1.x);
			vector.x = -1.57079637f;
			vector.z = 0.0f;
			return NormalizeAngles(vector * 57.2958f);
		}
		Quaternion quaternion = Quaternion(q1.w, q1.z, q1.x, q1.y);
		vector.y = std::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
		vector.x = std::asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
		vector.z = std::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
		return NormalizeAngles(vector * 57.2958f);
	}
	
	Vector3 RotatePoint(Vector3 center, Vector3 origin, float angle) {
		float num = angle * 0.0174532924f;
		float num2 = -std::sin(num);
		float num3 = std::cos(num);
		origin.x -= center.x;
		origin.z -= center.z;
		float num4 = origin.x * num3 - origin.z * num2;
		float num5 = origin.x * num2 + origin.z * num3;
		float num6 = num4 + center.x;
		num5 += center.z;
		return Vector3(num6, origin.y, num5);
	}
	void RotateTriangle(Vector2& point1, Vector2& point2, Vector2& point3, float rotation) {
		const auto points_center = (point1 + point2 + point3) / 3;

		point1 -= points_center;
		point2 -= points_center;
		point3 -= points_center;

		const auto temp_x = point1.x;
		const auto temp_y = point1.y;
		const auto temp_x2 = point2.x;
		const auto temp_y2 = point2.y;
		const auto temp_x3 = point3.x;
		const auto temp_y3 = point3.y;

		const auto theta = DEG2RAD(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point1.x = temp_x * c - temp_y * s;
		point1.y = temp_x * s + temp_y * c;
		point2.x = temp_x2 * c - temp_y2 * s;
		point2.y = temp_x2 * s + temp_y2 * c;
		point3.x = temp_x3 * c - temp_y3 * s;
		point3.y = temp_x3 * s + temp_y3 * c;

		point1 += points_center;
		point2 += points_center;
		point3 += points_center;
	}
	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		return Vector2{ RAD2DEG(std::asin(dir.y / dir.Length())), RAD2DEG(-std::atan2(dir.x, -dir.z)) };
	}

}