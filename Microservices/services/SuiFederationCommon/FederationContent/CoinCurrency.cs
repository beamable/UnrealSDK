using System;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using SuiFederationCommon.Extensions;
using SuiFederationCommon.Models;
using UnityEngine;

namespace SuiFederationCommon.FederationContent
{
    /// <summary>
    /// Regular coin currency
    /// </summary>
    [ContentType(FederationContentTypes.RegularCoinType)]
    public class CoinCurrency : CurrencyContent, IFtBase
    {
        /// <summary>
        /// Default federation
        /// </summary>
        public CoinCurrency()
        {
            federation = new OptionalFederation
            {
                HasValue = true,
                Value = new Federation
                {
                    Service = SuiFederationSettings.MicroserviceName,
                    Namespace = SuiFederationSettings.SuiIdentityName
                }
            };
        }

        /// <summary>
        ///
        /// </summary>
        [SerializeField] public new string name;
        /// <summary>
        ///
        /// </summary>
        [SerializeField] public string symbol;
        /// <summary>
        ///
        /// </summary>
        [SerializeField] public int decimals;
        /// <summary>
        ///
        /// </summary>
        [SerializeField] public string image;
        /// <summary>
        ///
        /// </summary>
        [SerializeField] public string description;
        /// <summary>
        ///
        /// </summary>
        [SerializeField] public long initialSupply;

        /// <summary>
        /// name
        /// </summary>
        public string Name => name;
        /// <summary>
        /// symbol
        /// </summary>
        public string Symbol => symbol;
        /// <summary>
        /// decimals
        /// </summary>
        public int Decimals => decimals;
        /// <summary>
        /// image
        /// </summary>
        public string Image => image;
        /// <summary>
        /// description
        /// </summary>
        public string Description => description;
        /// <summary>
        /// initialSupply
        /// </summary>
        public long InitialSupply => initialSupply;
    }

    /// <summary>
    /// CoinCurrencyRef
    /// </summary>
    [Serializable]
    public class CoinCurrencyRef : ContentRef<CoinCurrency> { }

    /// <summary>
    /// CoinCurrencyLink
    /// </summary>
    [Serializable]
    public class CoinCurrencyLink : ContentLink<CoinCurrency> { }
}