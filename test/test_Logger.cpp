#include "gtest/gtest.h"

// Include the header file for the code being tested
#include "Logger.h"

// Test the LogLevelToString() function
TEST(Logger, LogLevelToString) {
    // Test the conversion of each log level to its corresponding string
    EXPECT_EQ(LogLevelToString(LogLevel::TRACE), "TRACE");
    EXPECT_EQ(LogLevelToString(LogLevel::DEBUG), "DEBUG");
    EXPECT_EQ(LogLevelToString(LogLevel::INFO), "INFO");
    EXPECT_EQ(LogLevelToString(LogLevel::WARNING), "WARNING");
    EXPECT_EQ(LogLevelToString(LogLevel::ERROR), "ERROR");
    EXPECT_EQ(LogLevelToString(LogLevel::FATAL), "FATAL");

    // Test the conversion of an unknown log level value to the "UNKNOWN" string
    EXPECT_EQ(LogLevelToString((LogLevel)999), "UNKNOWN");
}

// Test the GetCurrentTimeAsString() function
TEST(Logger, GetCurrentTimeAsString) {
    // Get the current time as a string
    std::string current_time = GetCurrentTimeAsString();

    // Verify that the string has the correct format (YYYY-MM-DD
    // HH:MM:SS.ssssss)
    std::regex time_regex("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{6}");
    EXPECT_TRUE(std::regex_match(current_time, time_regex));
}

// Test the Log class
TEST(Logger, Log) {
    // Capture the output of the log message
    testing::internal::CaptureStdout();

    // Create a log message using the LOG() macro
    LOG(INFO) << "This is a test log message";

    // Get the captured output as a string
    std::string output = testing::internal::GetCapturedStdout();

    // Verify that the log message was output to the standard output stream
    std::regex log_regex(
        "\\[INFO\\]\\[\\d{4}-\\d{2}-\\d{2} "
        "\\d{2}:\\d{2}:\\d{2}\\.\\d{6}\\]:This is a test log message\n");
    EXPECT_TRUE(std::regex_match(output, log_regex));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
