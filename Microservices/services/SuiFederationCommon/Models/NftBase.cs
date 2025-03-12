using Beamable.Common.Content;

namespace SuiFederationCommon.Models
{
    /// <summary>
    ///
    /// </summary>
    public interface INftBase
    {
        /// <summary>
        ///
        /// </summary>
        string Name { get; }
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
        SerializableDictionaryStringToString CustomProperties { get; }
    }
}