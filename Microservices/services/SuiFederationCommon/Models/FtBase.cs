namespace SuiFederationCommon.Models
{
    /// <summary>
    ///
    /// </summary>
    public interface IFtBase
    {
        /// <summary>
        ///
        /// </summary>
        string Name { get; }
        /// <summary>
        ///
        /// </summary>
        string Symbol { get; }
        /// <summary>
        ///
        /// </summary>
        int Decimals { get; }
        /// <summary>
        ///
        /// </summary>
        string Image { get; }
        /// <summary>
        ///
        /// </summary>
        string Description { get; }
        /// <summary>
        ///
        /// </summary>
        long InitialSupply { get; }
    }
}