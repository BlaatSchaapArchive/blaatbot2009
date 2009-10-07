g++ --shared -fPIC bot.cpp bcp.cpp BotModule.cpp ../xmlParser.cpp -o libbot.so -lpthread -ldl
