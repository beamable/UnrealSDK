using System;
using System.Collections.Generic;
using Beamable.Common;
using Newtonsoft.Json;

namespace HathoraDemoCommon
{
    public class HathoraIdentity : IThirdPartyCloudIdentity
    {
        public string UniqueName => "hathora";
    }
    
    public static class Stats
    {
        public const string HathoraPings = "hathora_demo.pings";
    }

    [Serializable]
    public class HathoraCreateRoomRequest
    {
        public string roomConfig;
        public string region;
    }

    [Serializable]
    public class HathoraPortInfo
    {
        public string host;
        public string name;
        public int port;
        public string transportType;
    }

    [Serializable]
    public class HathoraConnectionInfo
    {
        public string processId;
        public string roomId;
        public string status;
        public HathoraPortInfo exposedPort;
        public List<HathoraPortInfo> additionalExposedPorts;
    }

    public class HathoraRealmConfig
    {
        public string AppId;
        public string DeveloperToken;
        public string FallbackRegion;
        public Uri HathoraURL;
    }

    public class MatchMakingConfig
    {
        public float PollingInterval;
        public float MaxWaitTime;
    }

    [Serializable]
    public class HathoraPingTimes
    {
        [JsonProperty("Los_Angeles")] public int LosAngeles;

        [JsonProperty("Chicago")] public int Chicago;

        [JsonProperty("Washington_DC")] public int WashingtonDc;

        [JsonProperty("Seattle")] public int Seattle;

        [JsonProperty("London")] public int London;

        [JsonProperty("Frankfurt")] public int Frankfurt;

        [JsonProperty("Sao_Paulo")] public int SaoPaulo;

        [JsonProperty("Tokyo")] public int Tokyo;

        [JsonProperty("Sydney")] public int Sydney;

        [JsonProperty("Singapore")] public int Singapore;

        [JsonProperty("Mumbai")] public int Mumbai;

        // create a + operator
        public static HathoraPingTimes operator +(HathoraPingTimes a, HathoraPingTimes b)
        {
            return new HathoraPingTimes
            {
                LosAngeles = a.LosAngeles + b.LosAngeles,
                Chicago = a.Chicago + b.Chicago,
                WashingtonDc = a.WashingtonDc + b.WashingtonDc,
                Seattle = a.Seattle + b.Seattle,
                London = a.London + b.London,
                Frankfurt = a.Frankfurt + b.Frankfurt,
                SaoPaulo = a.SaoPaulo + b.SaoPaulo,
                Tokyo = a.Tokyo + b.Tokyo,
                Sydney = a.Sydney + b.Sydney,
                Singapore = a.Singapore + b.Singapore,
                Mumbai = a.Mumbai + b.Mumbai
            };
        }

        public static HathoraPingTimes operator /(HathoraPingTimes a, int b)
        {
            return new HathoraPingTimes
            {
                LosAngeles = a.LosAngeles / b,
                Chicago = a.Chicago / b,
                WashingtonDc = a.WashingtonDc / b,
                Seattle = a.Seattle / b,
                London = a.London / b,
                Frankfurt = a.Frankfurt / b,
                SaoPaulo = a.SaoPaulo / b,
                Tokyo = a.Tokyo / b,
                Sydney = a.Sydney / b,
                Singapore = a.Singapore / b,
                Mumbai = a.Mumbai / b
            };
        }

        public List<KeyValuePair<string, int>> GetSortedPingTimes()
        {
            var pings = new List<KeyValuePair<string, int>>
            {
                new KeyValuePair<string, int>("Los_Angeles", LosAngeles),
                new KeyValuePair<string, int>("Chicago", Chicago),
                new KeyValuePair<string, int>("Washington_DC", WashingtonDc),
                new KeyValuePair<string, int>("Seattle", Seattle),
                new KeyValuePair<string, int>("London", London),
                new KeyValuePair<string, int>("Frankfurt", Frankfurt),
                new KeyValuePair<string, int>("Sao_Paulo", SaoPaulo),
                new KeyValuePair<string, int>("Tokyo", Tokyo),
                new KeyValuePair<string, int>("Sydney", Sydney),
                new KeyValuePair<string, int>("Singapore", Singapore),
                new KeyValuePair<string, int>("Mumbai", Mumbai),
            };

            // Sort the list by ping value
            pings.Sort((firstPair, nextPair) => { return firstPair.Value.CompareTo(nextPair.Value); });

            return pings;
        }
    }
}