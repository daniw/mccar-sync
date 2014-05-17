#ifndef Payload_H
#define Payload_H

#include <boost/crc.hpp>
#include <iostream>

constexpr size_t getPayloadSize() { return 10 /*+cmd +crc*/; }

template <typename Payload>
class DataPacket
{
public:
	static_assert(sizeof(Payload) <= getPayloadSize(), "Payload too big");

	DataPacket()
	{ }

	DataPacket(Payload payload)
		: payload(std::move(payload))
    { }

	Payload payload;
	bool checksumIsOk = false;
};

template <typename Payload>
class RequestDataPacket : public DataPacket<Payload>
{
public:
	RequestDataPacket()
	{ }

	RequestDataPacket(Payload payload)
		: DataPacket<Payload>(std::move(payload))
    { }
};

template <typename Payload>
class ResponseDataPacket : public DataPacket<Payload>
{
public:
	ResponseDataPacket()
	{ }

	ResponseDataPacket(bool ack, Payload payload)
		: DataPacket<Payload>(std::move(payload))
		, ack(ack)
	{ }

	template <typename... Args>
	explicit ResponseDataPacket(bool ack, Args&&... params)
		: DataPacket<Payload>(Payload{std::forward<Args>(params)...})
		, ack(ack)
	{ }

	bool ack;
};

struct __attribute__ ((packed)) EmptyPayload { uint8_t alwaysZero = 0; };

template <>
class ResponseDataPacket<void> : public DataPacket<EmptyPayload>
{
public:
	ResponseDataPacket()
	{ }

	explicit ResponseDataPacket(bool ack)
		: DataPacket<EmptyPayload>(EmptyPayload{})
		, ack(ack)
	{ }

	bool ack;
};

class RestoreFlagsCheckpointContext
{
public:
	explicit RestoreFlagsCheckpointContext(std::ios_base& strm)
		: strm(strm)
	{
		//state.copyfmt(strm);
	}

	~RestoreFlagsCheckpointContext()
	{
		//strm.copyfmt(state);
	}

private:
	std::ios_base& strm;
	//std::ios state;
};

using crc_8 = boost::crc_optimal<8, 0x9B, 0, 0, false, false>;

template <typename Payload>
void writePayloadToStream(std::ostream& strm, crc_8& crc, const Payload& payload)
{
	RestoreFlagsCheckpointContext savedFlags{strm};
	strm.unsetf(std::ios_base::skipws);

	const unsigned char* pRawData = reinterpret_cast<const unsigned char*>(&payload);

	//data
	for (size_t i = 0; i < sizeof(Payload); ++i)
	{
		strm << pRawData[i];
		crc.process_byte(pRawData[i]);
	}

	//Padding
	for (size_t i = 0; i < (getPayloadSize() - sizeof(Payload)); ++i)
	{
		strm << static_cast<unsigned char>(0);
		crc.process_byte(0);
	}
}

template <typename Payload>
void readPayloadFromStream(std::istream& strm, crc_8& crc, Payload& payload)
{
	RestoreFlagsCheckpointContext savedFlags{strm};
	strm.unsetf(std::ios_base::skipws);

	unsigned char* pRawData = reinterpret_cast<unsigned char*>(&payload);

	//data
	for (size_t i = 0; i < sizeof(Payload); ++i)
	{
		unsigned char tmp;
		strm >> tmp;
		pRawData[i] = tmp;
		crc.process_byte(pRawData[i]);
	}

	//Padding
	for (size_t i = 0; i < (getPayloadSize() - sizeof(Payload)); ++i)
	{
		unsigned char padding;
		strm >> padding;
		crc.process_byte(padding);
	}
}

template <typename Payload>
std::ostream& operator <<(std::ostream& strm, const RequestDataPacket<Payload>& dataPacket)
{
	RestoreFlagsCheckpointContext savedFlags{strm};
	strm.unsetf(std::ios_base::skipws);

	crc_8 crc;

	strm << static_cast<unsigned char>(Payload::cmd_id);

	writePayloadToStream(strm, crc, dataPacket.payload);

	//checksum
	strm << static_cast<unsigned char>(crc.checksum());

	return strm;
}

template <typename Payload>
std::istream& operator >>(std::istream& strm, RequestDataPacket<Payload>& dataPacket)
{
	RestoreFlagsCheckpointContext savedFlags{strm};
	strm.unsetf(std::ios_base::skipws);

    crc_8 crc;

	readPayloadFromStream(strm, crc, dataPacket.payload);

	//checksum
	unsigned char slaveCalculatedCrc;
	strm >> slaveCalculatedCrc;
	dataPacket.checksumIsOk = static_cast<unsigned char>(crc.checksum()) == slaveCalculatedCrc;

	return strm;
}


template <typename Payload>
std::ostream& operator <<(std::ostream& strm, const ResponseDataPacket<Payload>& dataPacket)
{
	crc_8 crc;

	strm << (dataPacket.ack ? (unsigned char)(1) : (unsigned char)(0));

	writePayloadToStream(strm, crc, dataPacket.payload);

	//checksum
	strm << static_cast<unsigned char>(crc.checksum());

	return strm;
}

template <typename Payload>
std::istream& operator >>(std::istream& strm, ResponseDataPacket<Payload>& dataPacket)
{
	crc_8 crc;

	unsigned char ack;
	strm >> ack;
	dataPacket.ack = ack;

	readPayloadFromStream(strm, crc, dataPacket.payload);

	//checksum
	unsigned char slaveCalculatedCrc;
	strm >> slaveCalculatedCrc;
	dataPacket.checksumIsOk = static_cast<unsigned char>(crc.checksum()) == slaveCalculatedCrc;

	return strm;
}

struct __attribute__ ((packed)) MovePayload
{
    enum { cmd_id = 0x01 };
    uint8_t direction;
};

struct __attribute__ ((packed)) FollowLinePayload
{
    enum { cmd_id = 0x02 };
    uint8_t type;
    uint8_t speed;
};

struct __attribute__ ((packed)) ConfigPIDPayload
{
    enum { cmd_id = 0x03 };
    uint8_t kpleft;
    uint8_t kileft;
    uint8_t kdleft;
    uint8_t kpright;
    uint8_t kiright;
    uint8_t kdright;
};

struct __attribute__ ((packed)) LEDColorPayload
{
    enum { cmd_id = 0x04 };
    uint8_t redleft;
    uint8_t greenleft;
    uint8_t blueleft;
    uint8_t redright;
    uint8_t greenright;
    uint8_t blueright;
};

struct __attribute__ ((packed)) ColorSensorPayload
{
    enum { cmd_id = 0x05 };
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct __attribute__ ((packed)) AccelerationPayload
{
    enum { cmd_id = 0x06 };
    uint8_t xhigh;
    uint8_t xlow;
    uint8_t yhigh;
    uint8_t ylow;
    uint8_t zhigh;
    uint8_t zlow;
};

struct __attribute__ ((packed)) BeepPayload
{
    enum { cmd_id = 0x07 };
    uint8_t bufferNo;
};

struct __attribute__ ((packed)) RequestDataPayload
{
	enum { cmd_id = 0x08 };
	uint8_t bufferNoHigh;
	uint8_t bufferNoLow;
};

struct __attribute__ ((packed)) WriteDataPayload
{
	enum { cmd_id = 0x09 };
	uint8_t bufferNoHigh;
	uint8_t bufferNoLow;
	uint8_t offsetHigh;
	uint8_t offsetLow;
	uint8_t data[getPayloadSize() - 4];
};

struct __attribute__ ((packed)) HandleRequestedDataPayload
{
	enum { cmd_id = 0x0A };
	uint8_t bufferNoHigh;
	uint8_t bufferNoLow;
	uint8_t data[getPayloadSize() - 2] = {};
};

struct __attribute__ ((packed)) NotifyVersionPayload
{
    enum { cmd_id = 0x10 };
    uint8_t version;
};


struct __attribute__ ((packed)) StatusPayload
{
	enum { cmd_id = 0x0d };
	uint8_t taskQueueLoad;
	uint8_t usedPages;
	uint8_t freePages;
	uint8_t pageSize;
	uint8_t usedReceiveQueue;
	uint8_t freeReceiveQueue;
};

#endif // Payload_H
