namespace StringConverter {
	std::wstring ToUnicode(const std::string& str) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.from_bytes(str);
	}

	std::string ToASCII(const std::wstring& wstr) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.to_bytes(wstr);
	}
}
float timee = 120.f;
UINT vps = 1;
WNDPROC original_windowproc = nullptr;
bool sdk_initialized = false;
bool timer_initialized = false;
float timeSinceStartup = 0;
float timeFrequency = 0;
float get_time_since_startup() {
	LARGE_INTEGER PerformanceCount;
	LARGE_INTEGER FrequencyCount;

	if (!timer_initialized) {
		timer_initialized = true;

		PerformanceCount.QuadPart = 0;
		QueryPerformanceCounter(&PerformanceCount);

		FrequencyCount.QuadPart = 0;
		QueryPerformanceFrequency(&FrequencyCount);

		timeFrequency = float(FrequencyCount.QuadPart);

		timeSinceStartup = float(PerformanceCount.QuadPart);
	}

	PerformanceCount.QuadPart = 0;
	QueryPerformanceCounter(&PerformanceCount);

	return float(PerformanceCount.QuadPart - timeSinceStartup) / timeFrequency;
}
class LogSystem {
public:
	static inline int max_entries = 10;

	static void draw_text(Vector2, std::wstring);
	static void draw_line(Vector2, Vector2);

	struct LogEntry {
	public:
		std::wstring message;
		float startedAt;
		float duration;

		LogEntry(std::wstring message, float duration) {
			this->message = message;
			this->duration = duration;
			this->startedAt = get_time_since_startup();
		}
	};

	static inline std::vector<LogEntry> logs = std::vector<LogEntry>();
	static inline std::vector<Explosion> loggedExplosions = std::vector<Explosion>();
	static inline std::vector<BulletTracer> bulletTracers = std::vector<BulletTracer>( );
	static inline std::vector<TraceResult> traceResults = std::vector<TraceResult>( );

	static void Log(std::wstring message, float duration) {
		if (logs.size() >= max_entries)
			logs.erase(logs.begin());

		logs.push_back(LogEntry(message, duration));
	}
	static void AddTraceResult(TraceResult res) {
		traceResults.push_back(res);

		if (traceResults.size( ) > 1)
			traceResults.erase(traceResults.begin( ));
	}
	static void AddTracer(Vector3 start, Vector3 end) {
		bulletTracers.push_back(BulletTracer(start, end));

		if (bulletTracers.size( ) > 1)
			bulletTracers.erase(bulletTracers.begin( ));
	}
	static void LogExplosion(std::string type, Vector3 pos) {
		bool explosionCollision = false;
		std::vector<Explosion>::iterator it;
		for (it = loggedExplosions.begin(); it != loggedExplosions.end(); it++) {
			Vector2 explPos;
			if (it->position.Distance(pos) <= 25.0f) {
				explosionCollision = true;
				break;
			}
		}
		if (!explosionCollision) {
			Explosion explosion = Explosion();
			explosion.name = StringFormat::format(xorstr("%s Raid"), type.c_str());
			explosion.position = pos;
			explosion.timeSince = get_time_since_startup();
			loggedExplosions.push_back(explosion);
		}
	}

	static void Render( ) {
		float yPos = 30.0f;
		for (int i = 0; i < logs.size( ); i++) {
			LogEntry entry = logs[ i ];
			if ((get_time_since_startup( ) - entry.startedAt) >= entry.duration) {
				logs.erase(logs.begin( ) + i);
				continue;
			}
			draw_text(Vector2(200, yPos), entry.message);
			yPos += 15.0f;
		}
	}
	static void RenderTracers( ) {
		for (int i = 0; i < bulletTracers.size( ); i++) {
			BulletTracer tracer = bulletTracers[ i ];
			
			Vector2 s_pos_start; Vector2 s_pos_end;
			if (utils::w2s(tracer.start, s_pos_start) && utils::w2s(tracer.end, s_pos_end)) {
				draw_line(s_pos_start, s_pos_end);
			}
		}
	}
	static void RenderTraceResults( ) {
		for (int i = 0; i < traceResults.size( ); i++) {
			TraceResult tracer = traceResults[ i ];

			Vector2 s_pos_end;
			if (utils::w2s(tracer.hitPosition, s_pos_end)) {
				//draw_line(s_pos_start, s_pos_end);
				Renderer::Circle(s_pos_end, D2D1::ColorF::Blue, 5.f);
			}
		}
	}
	static void RenderExplosions() {
		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince) >= timee) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}
			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;
			if (utils::w2s(explosion.position, explPos)) {
				Renderer::Text(
					explPos,
					D2D1::ColorF::Red,
					true,
					true,
					StringConverter::ToUnicode(StringFormat::format(xorstr("%s [%.2fm] [%d]"),
						explosion.name.c_str(),
						Math::Distance_3D(explosion.position, LocalPlayer::Entity()->get_bone_pos(head)),
						(int)(timee - (get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince)))).c_str()
				);
			}
		}
	}
};
void LogSystem::draw_text(Vector2 pos, std::wstring str) {
	Renderer::Text(pos, D2D1::ColorF::Red, false, true, str.c_str( ));
}
void LogSystem::draw_line(Vector2 pos, Vector2 pos2) {
	Renderer::Line(pos, pos2, D2D1::ColorF::Red, 1.f, true);
}

