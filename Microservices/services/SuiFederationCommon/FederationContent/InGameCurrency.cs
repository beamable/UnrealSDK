using System;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using SuiFederationCommon.Extensions;
using SuiFederationCommon.Models;
using UnityEngine;

namespace SuiFederationCommon.FederationContent
{
    /// <summary>
    /// In game coin currency
    /// </summary>
    [ContentType(FederationContentTypes.InGameCoinType)]
    public class InGameCurrency : CurrencyContent, IFtBase
    {
        /// <summary>
        /// Default federation
        /// </summary>
        public InGameCurrency()
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
        /// name
        /// </summary>
        [SerializeField] public new string name;
        /// <summary>
        /// symbol
        /// </summary>
        [SerializeField] public string symbol;
        /// <summary>
        /// decimals
        /// </summary>
        [SerializeField] public int decimals;
        /// <summary>
        /// image
        /// </summary>
        [SerializeField] public string image;
        /// <summary>
        /// description
        /// </summary>
        [SerializeField] public string description;
        /// <summary>
        /// initialSupply
        /// </summary>
        [SerializeField] public long initialSupply;
        /// <summary>
        /// allowSpending
        /// </summary>
        [SerializeField] public bool allowSpending = true;
        /// <summary>
        /// allowSpending
        /// </summary>
        [SerializeField] public bool allowBuying = true;
        /// <summary>
        /// allowSpending
        /// </summary>
        [SerializeField] public bool allowTransfers;

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
        /// <summary>
        /// allowSpending
        /// </summary>
        public bool AllowSpending => allowSpending;
        /// <summary>
        /// allowSpending
        /// </summary>
        public bool AllowBuying => allowBuying;
        /// <summary>
        /// allowTransfers
        /// </summary>
        public bool AllowTransfers => allowTransfers;
    }

    /// <summary>
    /// InGameCurrencyRef
    /// </summary>
    [Serializable]
    public class InGameCurrencyRef : ContentRef<InGameCurrency> { }

    /// <summary>
    /// InGameCurrencyLink
    /// </summary>
    [Serializable]
    public class InGameCurrencyLink : ContentLink<InGameCurrency> { }
}