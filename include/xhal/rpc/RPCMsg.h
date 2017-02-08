#ifndef __RPCMSG_H
#define __RPCMSG_H

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

/*
 * This is a generic RPC Message, it can contain whatever parameters are
 * necessary for the request.  The parameter "method" determines the function
 * to be called on the remote system.  i.e. "memory.read"
 */

class RPCMsg {
	protected:
		class Field {
			public:
				enum Datatype {
					DATATYPE_NONE = 0,
					DATATYPE_STRING,
					DATATYPE_STRING_ARRAY,
					DATATYPE_WORD,
					DATATYPE_WORD_ARRAY,
					DATATYPE_BINARYDATA
				};
				enum Datatype type;
				std::string data;
				Field(enum Datatype type, std::string data) : type(type), data(data) { };
		};
		std::map<std::string, Field> fields;
		void validate_key(std::string key) const;
		void validate_key(std::string key, enum Field::Datatype require_type) const;

	public:
		static const char key_characters[];
		// "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._";

		class BadKeyException {
			public:
				const std::string key;
				BadKeyException(std::string key) : key(key) { };
		};
		class TypeException { };
		class BufferTooSmallException { };
		class CorruptMessageException {
			public:
				const std::string reason;
				CorruptMessageException(std::string reason) : reason(reason) { };
		};

		RPCMsg() { RPCMsg(""); };
		RPCMsg(std::string method_name);
		RPCMsg(void *serial_data, uint32_t datalen);
		std::string serialize() const;

		bool get_key_exists(std::string key) const;

		std::string get_string(std::string key) const;
		void set_string(std::string key, std::string value);

		uint32_t get_string_array_size(std::string key) const;
		std::vector<std::string> get_string_array(std::string key) const;
		void set_string_array(std::string key, std::vector<std::string> value);

		uint32_t get_word(std::string key) const;
		void set_word(std::string key, uint32_t value);

		uint32_t get_word_array_size(std::string key) const;
		void get_word_array(std::string key, uint32_t *data) const;
		void set_word_array(std::string key, uint32_t *data, int count);

		uint32_t get_binarydata_size(std::string key) const;
		void get_binarydata(std::string key, void *data, uint32_t bufsize) const;
		void set_binarydata(std::string key, const void *data, uint32_t bufsize);
};

#endif
