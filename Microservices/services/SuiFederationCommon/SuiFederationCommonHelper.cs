using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace SuiFederationCommon
{
    /// <summary>
    /// SuiFederationCommonHelper
    /// </summary>
    public static class SuiFederationCommonHelper
    {
        /// <summary>
        /// Get federation types
        /// </summary>
        /// <returns></returns>
        public static HashSet<Type> GetFederationTypes()
        {
            return Assembly.GetExecutingAssembly()
                .GetTypes()
                .Where(t => t.Namespace == "SuiFederationCommon.FederationContent")
                .ToHashSet();
        }
    }
}