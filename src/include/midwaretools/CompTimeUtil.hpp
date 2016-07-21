/*
 * CompTimeUtil.hpp
 *
 *  Created on: Mar 16, 2015
 *      Author: dehann
 */

#ifndef COMPTIMEUTIL_HPP_
#define COMPTIMEUTIL_HPP_

#include <string>
#include <sys/time.h>

#include <midwaretools/PracticalSocket.h>

//#define COMPTIME_ADDR      "128.30.27.116"
#define COMPTIME_ADDR      "127.0.0.1"
#define COMPTIME_PORT       9999
#define COMPTIME_SEND_PORT 10000

using namespace std;

static int nextPort = COMPTIME_SEND_PORT;

class CompTimeUtil {
private:
  double minTime;
  double maxTime;
  double prevStart;
  double tStart;
  double elapsed;
  double tocTime;
  double usage;
  string name;

  UDPSocket* _showTimeClient;

  double tictimer() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((double)t.tv_sec + ((double)t.tv_usec)/1000000.);
  }

  double toctimer(double t) {
    double s = tictimer();
    return (max(0., s-t));
  }

public:
  CompTimeUtil() {
    reset();
    setName("NOINIT");

    _showTimeClient = new UDPSocket(nextPort++);
  }

  ~CompTimeUtil() {
    _showTimeClient->disconnect();
    delete _showTimeClient;
  }

  void setName(string _n) {
    name = _n;
  }

  void reset() {
    minTime = 999999999999999.;
    maxTime = 0.;
    tStart = 0.;
    prevStart = 0.;
    elapsed = 0.;
    tocTime = 0.;
    usage = 0.;
  }

  void sendTimeData() {
    std::stringstream ss;

    // {"start": 0.034, "end": 0.04}
    ss << "{";
    ss << "\"NAME\": \"" << name << "\"";
    ss << ", ";
    ss << "\"COMPTIME\": " << elapsed;
    ss << ", ";
    ss << "\"MAXTIME\": " << maxTime;
    ss << ", ";
    ss << "\"MINTIME\": " << minTime;
    ss << ", ";
    ss << "\"SPARETIME\": " << (tStart-tocTime);
    ss << ", ";
    ss << "\"USAGE\": " << usage;
    ss << "}" << endl;

    //cout << "CompTimeUtil::sendTimeData -- sending a UDP packet, size " << ss.str().length() << " to " << COMPTIME_ADDR << ":" << COMPTIME_PORT << endl;
    if (minTime < 99999999999999) {
      _showTimeClient->sendTo(ss.str().c_str(), ss.str().length(), COMPTIME_ADDR, COMPTIME_PORT);
    } else {
      cout << "CompTimeUtil::sendTimeData -- not sending large minTime packet" << endl;
    }
  }

  void begin() {
    prevStart = tStart;
    tStart = tictimer();

    sendTimeData();
  }

  void after() {
    elapsed = toctimer(tStart);
    tocTime = tStart + elapsed;
    if (maxTime < elapsed) {
      maxTime = elapsed;
    }
    if (minTime > elapsed) {
      minTime = elapsed;
    }

    usage = elapsed/(tStart-prevStart);
  }

};



#endif /* COMPTIMEUTIL_HPP_ */
