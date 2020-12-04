/***************************************************************************
* Copyright (c) 2020, QuantStack and xeus-SQLite contributors              *
*                                                                          *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XEUS_SOCI_INTERPRETER_HPP
#define XEUS_SOCI_INTERPRETER_HPP

#include "nlohmann/json.hpp"
#include "xeus/xinterpreter.hpp"

namespace nl = nlohmann;

namespace xeus_sqlite
{
    class XEUS_SQLITE_API interpreter : public xeus::xinterpreter
    {
    friend class SQLite::Database;

    public:

        interpreter() = default;
        virtual ~interpreter() = default;

    private:
        std::unique_ptr<SQLite::Database> m_db = nullptr;
        std::unique_ptr<SQLite::Database> m_backup_db = nullptr;
        bool m_bd_is_loaded = false;
        std::string m_db_path;

        void configure_impl() override;
        nl::json execute_request_impl(int execution_counter,
                                      const std::string& code,
                                      bool silent,
                                      bool store_history,
                                      nl::json user_expressions,
                                      bool allow_stdin) override;
        nl::json complete_request_impl(const std::string& code,
                                       int cursor_pos) override;
        nl::json inspect_request_impl(const std::string& code,
                                      int cursor_pos,
                                      int detail_level) override;
        nl::json is_complete_request_impl(const std::string& code) override;
        nl::json kernel_info_request_impl() override;
        void shutdown_request_impl() override;
    };
}

#endif