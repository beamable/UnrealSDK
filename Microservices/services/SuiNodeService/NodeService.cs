using System.Threading.Tasks;
using Jering.Javascript.NodeJS;

namespace SuiNodeServicve
{
    /// <summary>
    /// Service for calling SUI SDK functions
    /// </summary>
    public static class NodeService
    {
        private const string BridgeModulePath = "js/bridge.js";

        /// <summary>
        /// Creates SUI wallet keypair
        /// </summary>
        /// <returns></returns>
        public static async Task<string> CreateWallet()
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "createWallet") ?? "";
        }

        /// <summary>
        /// Import SUI wallet from a private key
        /// </summary>
        /// <returns></returns>
        public static async Task<string> ImportWallet(string privateKey)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "importWallet",
                new object[] { privateKey }) ?? "";
        }

        /// <summary>
        /// Import SUI wallet from a private key
        /// </summary>
        /// <returns></returns>
        public static async Task<bool> VerifySignature(string token, string challenge, string solution)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<bool>(
                BridgeModulePath,
                "verifySignature",
                new object[] { token, challenge, solution });
        }

        /// <summary>
        /// Mint regular coin
        /// </summary>
        /// <param name="mintRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> MintRegularCoin(string mintRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "mintRegularCoin",
                new object[] { mintRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// Burn regular coin
        /// </summary>
        /// <param name="mintRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> BurnRegularCoin(string mintRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "burnRegularCoin",
                new object[] { mintRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// Mint game coin
        /// </summary>
        /// <param name="mintRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> MintGameCoin(string mintRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "mintGameCoin",
                new object[] { mintRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// Burn game coin
        /// </summary>
        /// <param name="mintRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> BurnGameCoin(string mintRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "burnGameCoin",
                new object[] { mintRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// CoinBalance
        /// </summary>
        /// <param name="wallet"></param>
        /// <param name="requestJson"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> CoinBalance(string wallet, string requestJson, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "getBalance",
                new object[] { wallet, requestJson, environment }) ?? "";
        }

        /// <summary>
        /// GetGameCoinBalance
        /// </summary>
        /// <param name="wallet"></param>
        /// <param name="requestJson"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> GetGameCoinBalance(string wallet, string requestJson, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "getGameCoinBalance",
                new object[] { wallet, requestJson, environment }) ?? "";
        }

        /// <summary>
        /// Mint NFTs
        /// </summary>
        /// <param name="mintRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> MintNfts(string mintRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "mintNfts",
                new object[] { mintRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// GetOwnedObjects
        /// </summary>
        /// <param name="wallet"></param>
        /// <param name="packageId"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> GetOwnedObjects(string wallet, string packageId, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "getOwnedObjects",
                new object[] { wallet, packageId, environment }) ?? "";
        }

        /// <summary>
        /// UpdateNfts
        /// </summary>
        /// <param name="updateRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> UpdateNfts(string updateRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "updateNft",
                new object[] { updateRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// DeleteNfts
        /// </summary>
        /// <param name="deleteRequestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> DeleteNfts(string deleteRequestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "burnNft",
                new object[] { deleteRequestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// SetNftContractOwner
        /// </summary>
        /// <param name="requestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> SetNftContractOwner(string requestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "setNftContractOwner",
                new object[] { requestJson, realmAccountPrivateKey, environment }) ?? "";
        }

        /// <summary>
        /// ObjectExists
        /// </summary>
        /// <param name="objectId"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> ObjectExists(string objectId, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "objectExists",
                new object[] { objectId, environment }) ?? "";
        }

        /// <summary>
        /// WithdrawCurrency
        /// </summary>
        /// <param name="requestJson"></param>
        /// <param name="realmAccountPrivateKey"></param>
        /// <param name="environment"></param>
        /// <returns></returns>
        public static async Task<string> WithdrawCurrency(string requestJson, string realmAccountPrivateKey, string environment)
        {
            return await StaticNodeJSService.InvokeFromFileAsync<string>(
                BridgeModulePath,
                "withdrawCurrency",
                new object[] { requestJson, realmAccountPrivateKey, environment }) ?? "";
        }
    }
}