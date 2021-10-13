
#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#ifndef SQL_BUILDER_
#define SQL_BUILDER_

namespace time_format
{
struct FormatDate
{
};

struct FormatTime
{
};

inline FormatDate date()
{
    return FormatDate{};
}

inline FormatTime time()
{
    return FormatTime{};
}
}; // namespace time_format

template <typename T> inline std::string to_value(const T &value)
{
    return std::to_string(value);
}

template <> inline std::string to_value<float>(const float &value)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}

template <> inline std::string to_value<std::string>(const std::string &value)
{
    std::string str;
    str.append("'");
    str.append(value);
    str.append("'");

    return str;
}

inline std::string time_t_to_str(const time_t &time, time_format::FormatDate)
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
}

inline std::string time_t_to_str(const time_t &time, time_format::FormatTime)
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");
    return ss.str();
}

std::string column_list(const std::vector<std::string> &columns,
                        const char *seperator)
{
    std::string result;

    std::for_each(std::begin(columns), std::prev(std::end(columns)),
                  [&](const auto &column) {
                      result.append(column);
                      result.append(seperator);
                  });

    result.append(*std::prev(std::end(columns)));

    return result;
}

class SQLInsertBuilder
{
    std::string m_sql_command;
    std::string m_table;

    std::vector<std::string> m_params;
    std::vector<std::string> m_values;

    std::function<bool(const std::string &)> param_already_inserted;

  public:
    SQLInsertBuilder()
    {
        param_already_inserted = [&](const std::string &param) -> bool {
            return std::find(std::begin(m_params), std::end(m_params), param) !=
                   std::end(m_params);
        };
    }

    virtual ~SQLInsertBuilder()
    {
    }

    SQLInsertBuilder &into(const std::string &table)
    {
        m_table = table;
        return *this;
    }

    template <typename T>
    SQLInsertBuilder &insert(std::string param, const T &value)
    {
        if (not param_already_inserted(param))
        {
            m_params.push_back(param);
            m_values.push_back(to_value(value));
        }

        return *this;
    }

    template <typename T>
    SQLInsertBuilder operator()(std::string param, const T &value)
    {
        insert(param, value);
        return *this;
    }

    operator const std::string &()
    {
        m_sql_command.clear();

        m_sql_command.append("insert into ");
        m_sql_command.append(m_table);

        m_sql_command.append(" (");
        m_sql_command.append(column_list(m_params, ","));
        m_sql_command.append(") values(");
        m_sql_command.append(column_list(m_values, ","));
        m_sql_command.append(");");

        return m_sql_command;
    }
};

#endif // SQL_BUILDER_
