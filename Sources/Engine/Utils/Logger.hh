#pragma once

#include <Common.hh>


#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

#include <ConfigTypes.hh>



NAMESPACE_BEGIN

#define LOGGER_FILE_NAME "engine.log"

#define ENGINE_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define ENGINE_INFO(...) spdlog::info(__VA_ARGS__)
#define ENGINE_WARN(...) spdlog::warn(__VA_ARGS__)
#define ENGINE_ERROR(...) spdlog::error(__VA_ARGS__)

#define ENGINE_VALIDLOCATION(file_or_location) ENGINE_INFO("Loading Asset: {}\nAbsolute Path: {}\nAccessible: {}", file_or_location.string(), fs::absolute(file_or_location).string(), fs::exists(file_or_location))

using LoggerPtr = std::shared_ptr<spdlog::logger>;
/*
this is a singleton class with all method static. 
create instance with: Logger::Init, use singleton with Logger::Get*/
class Logger {

/*

*/
public:
    static void Init( const cfgAppContext& config, const std::string& logfile = LOGGER_FILE_NAME) {
        //parse config
        bool consoleoutput = config.consoleoutput;
        bool fileoutput = config.fileoutput;
        bool fileoutputappend = config.fileoutputappend;


        // 线程池 (1 个线程, 8192 队列大小)
        spdlog::init_thread_pool(8192, 1);

        // 控制台带颜色输出
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%T] [%^%l%$] %v");

        // 文件输出 (异步)
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile, fileoutputappend);

        std::vector<spdlog::sink_ptr> sinks {  };

        if (consoleoutput)
            sinks.push_back(console_sink);
        if (fileoutput) 
            sinks.push_back(file_sink);

        // 异步 logger
        logger = std::make_shared<spdlog::async_logger>(
            "ENGINE",
            sinks.begin(), sinks.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::block);

        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);

        spdlog::set_level(spdlog::level::trace); // 设置全局最低日志等级
        spdlog::flush_on(spdlog::level::warn);   // warn 及以上立即 flush
    }

    static void Shutdown() {
    if (logger) {
        ENGINE_INFO("Shutting down logger...");
        logger->flush();
        spdlog::drop_all();     // 清空注册的 logger
        spdlog::shutdown();     // 停止后台线程并释放资源
        logger.reset();
    }
}

    static std::shared_ptr<spdlog::logger>& Get() { return logger; }

private:
//static logger itself
    static std::shared_ptr<spdlog::logger> logger;
};






NAMESPACE_END












