using System;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using SuiFederationCommon.Extensions;
using SuiFederationCommon.Models;
using UnityEngine;

namespace SuiFederationCommon.FederationContent
{
    /// <summary>
    /// SwordItem NFT
    /// </summary>
    [ContentType(FederationContentTypes.WeaponItemType)]
    public class WeaponItem : ItemContent, INftBase
    {
        /// <summary>
        /// Default federation
        /// </summary>
        public WeaponItem()
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

        [SerializeField] private new string name = "";
        [SerializeField] private string description = "";
        [SerializeField] private string image = "";
        [SerializeField] private SerializableDictionaryStringToString customProperties = new SerializableDictionaryStringToString();

        /// <summary>
        /// Token name
        /// </summary>
        public string Name => name;

        /// <summary>
        /// Token description
        /// </summary>
        public string Description => description;

        /// <summary>
        /// Token image
        /// </summary>
        public string Image => image;

        /// <summary>
        /// Token custom properties
        /// </summary>
        public SerializableDictionaryStringToString CustomProperties => customProperties;
    }

    /// <summary>
    /// WeaponItemItemRef
    /// </summary>
    [Serializable]
    public class WeaponItemRef : ContentRef<WeaponItem>
    {
    }

    /// <summary>
    /// WeaponItemLink
    /// </summary>
    [Serializable]
    public class WeaponItemLink : ContentLink<WeaponItem>
    {
    }
}