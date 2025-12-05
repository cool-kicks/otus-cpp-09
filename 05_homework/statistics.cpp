#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <limits>

class IStatistics {
public:
	virtual ~IStatistics() {}
	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {}
	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}
	double eval() const override {
		return m_min;
	}
	const char * name() const override {
		return "min";
	}
private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() :  m_max{std::numeric_limits<double>::lowest()}{}
	void update(double next) override{
		if(next > m_max){
			m_max = next;
		}
	}
	double eval() const override {
        return m_max;
    }
	const char* name() const override{
		return "max";
	}
private:
	double m_max;
};

class Mean : public IStatistics{
public:
	Mean() : m_sum{0.0}, m_count{0} {}
	void update(double next) override{
		m_sum += next;
		m_count++;
	}
	double eval() const override{
		return(m_count ? m_sum / m_count : 0);
	}
	const char* name() const override{
		return "mean";
	}

private:
	double m_sum;
	size_t m_count;
};

class Stda : public IStatistics {
public:
    void update(double next) override {
        m_values.push_back(next);
    }

    double eval() const override {
        if (m_values.size() <= 1) return 0;

        double sum = 0.0;
        for (double v : m_values) sum += v;
        double mean = sum / m_values.size();

        double acc = 0.0;
        for (double v : m_values)
            acc += (v - mean) * (v - mean);

        return std::sqrt(acc / m_values.size());
    }

    const char* name() const override { return "std"; }

private:
    std::vector<double> m_values;
};


class Percentile : public IStatistics {
public:
    Percentile(double pct) : m_pct(pct) {}

    void update(double next) override {
        m_values.push_back(next);
    }

    double eval() const override {
        if (m_values.empty()) return 0;

        std::vector<double> sorted = m_values;
        std::sort(sorted.begin(), sorted.end());

        double idx = m_pct * (sorted.size() - 1);
        size_t idx_below = static_cast<size_t>(std::floor(idx));
        size_t idx_above = static_cast<size_t>(std::ceil(idx));

        if (idx_below == idx_above)
            return sorted[idx_below];

        double fraction = idx - idx_below;
        return sorted[idx_below] + fraction * (sorted[idx_above] - sorted[idx_below]);
    }

    const char* name() const override {
        static char buf[16];
        sprintf(buf, "pct%.0f", m_pct * 100);
        return buf;
    }

private:
    std::vector<double> m_values;
    double m_pct;
};




int main() {

	std::vector<double> values;
    double val = 0.0;
    while (std::cin >> val) {
        values.push_back(val);
    }

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Stda{};
	statistics[4] = new Percentile(0.90);
	statistics[5] = new Percentile(0.95);

	for (double x : values)
        for (size_t i = 0; i < statistics_count; ++i)
            statistics[i]->update(x);

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}