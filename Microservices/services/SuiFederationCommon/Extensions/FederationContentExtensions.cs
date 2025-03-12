using System.Linq;
using Beamable.Common.Inventory;
using SuiFederationCommon.FederationContent;

namespace SuiFederationCommon.Extensions
{
    /// <summary>
    /// FederationContentExtensions
    /// </summary>
    public static class FederationContentExtensions
    {
        /// <summary>
        /// CoinCurrency module name
        /// </summary>
        /// <param name="coinCurrency"></param>
        /// <returns></returns>
        public static string ToModuleName(this CoinCurrency coinCurrency)
            => SanitizeModuleName(coinCurrency.name).ToLowerInvariant();

        /// <summary>
        /// InGameCurrency module name
        /// </summary>
        /// <param name="coinCurrency"></param>
        /// <returns></returns>
        public static string ToModuleName(this InGameCurrency coinCurrency)
            => SanitizeModuleName(coinCurrency.name).ToLowerInvariant();

        /// <summary>
        /// ItemContent module name
        /// </summary>
        /// <param name="itemContent"></param>
        /// <returns></returns>
        public static string ToModuleName(this ItemContent itemContent)
            => SanitizeModuleName(itemContent.ContentType.Split('.').Last()).ToLowerInvariant();

        /// <summary>
        /// Get content type part for NFTs
        /// </summary>
        /// <param name="contentId"></param>
        /// <returns></returns>
        public static string ToContentType(this string contentId)
            => contentId.Contains('.') ? contentId[..contentId.LastIndexOf('.')] : contentId;

        /// <summary>
        /// RegularCoinPrefix
        /// </summary>
        public static string RegularCoinPrefix => $"currency.{FederationContentTypes.RegularCoinType}";

        /// <summary>
        /// NFTPrefix
        /// </summary>
        public static string NftPrefix => "items.";

        /// <summary>
        /// RegularCoinModuleName
        /// </summary>
        public static string SanitizeModuleName(string module)
            => module.Replace("_", "").Replace("-", "").Replace(" ", "");
    }

    /// <summary>
    /// Federation Content Type Names
    /// </summary>
    public static class FederationContentTypes
    {
        /// <summary>
        /// Regular coin type name
        /// </summary>
        public const string RegularCoinType = "coin";

        /// <summary>
        /// In game coin type name
        /// </summary>
        public const string InGameCoinType = "game_coin";

        /// <summary>
        /// Weapon type name
        /// </summary>
        public const string WeaponItemType = "weapon";
    }
}