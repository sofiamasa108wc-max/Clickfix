#include <Geode/Geode.hpp>
#include <deque>
#include <chrono>
#include <algorithm>

using namespace geode::prelude;

namespace clickfix {
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    struct BufferedPress {
        TimePoint receivedAt;
        bool player1;
    };

    // Small, deterministic timing core. This does not synthesize game input by itself;
    // the game-specific PlayerObject hook must consume/replay entries safely.
    class InputBuffer {
    public:
        void push(bool player1, TimePoint now = Clock::now()) {
            m_pending.push_back({ now, player1 });
        }

        bool popIfFresh(bool& player1, int toleranceMs, TimePoint now = Clock::now()) {
            prune(toleranceMs, now);
            if (m_pending.empty()) return false;
            player1 = m_pending.front().player1;
            m_pending.pop_front();
            return true;
        }

        void clear() { m_pending.clear(); }

    private:
        std::deque<BufferedPress> m_pending;

        void prune(int toleranceMs, TimePoint now) {
            auto const limit = std::chrono::milliseconds(std::clamp(toleranceMs, 0, 500));
            while (!m_pending.empty() && now - m_pending.front().receivedAt > limit) {
                m_pending.pop_front();
            }
        }
    };

    static InputBuffer s_buffer;
}

$on_mod(Loaded) {
    auto* mod = Mod::get();
    int tolerance = mod->getSettingValue<int>("tolerance_ms");
    log::info("ClickFix loaded. Configured tolerance: {} ms", tolerance);
    log::warn("ClickFix v0.1.0 is a source scaffold: gameplay input hooks are not enabled yet.");
}
