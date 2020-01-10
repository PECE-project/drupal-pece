export const menuHeader = [
  {
    label: 'home',
    routeName: 'home'
  },
  {
    label: 'about',
    routeName: 'about'
  },
  {
    label: 'collaborate',
    routeName: 'collaborate'
  },
  {
    label: 'analyze',
    routeName: 'analyze'
  },
  {
    label: 'discover',
    routeName: 'discover'
  }
]

export const filter = [
  { label: 'Artifact - Audio' },
  { label: 'Artifact - Bundle' },
  { label: 'Artifact - Image' },
  { label: 'Artifact - PDF Document' },
  { label: 'Artifact - Text' },
  { label: 'Artifact - Website' },
  { label: 'Group' },
  { label: 'Memo' },
  { label: 'PECE Essay' },
  { label: 'Photo Essay' }
]

export const users = [
  {
    id: 1,
    fullname: 'Julia Morgen',
    slug: 'julia-morgen',
    image: {
      alt: 'Avatar Julia Morgen',
      url: 'https://images-na.ssl-images-amazon.com/images/M/MV5BMTkzNjE5MzY5M15BMl5BanBnXkFtZTgwMDI5ODMxODE@._V1_UY256_CR98,0,172,256_AL_.jpg'
    }
  },
  {
    id: 2,
    fullname: 'Jack Phill',
    slug: 'jack-phill',
    image: {
      alt: 'avatar Jack Phill',
      url: 'https://randomuser.me/api/portraits/men/46.jpg'
    }
  },
  {
    id: 3,
    fullname: 'Julio Tyson',
    slug: 'julio-tyson',
    image: {
      alt: 'Avatar Julio Tyson',
      url: 'https://pbs.twimg.com/profile_images/969073897189523456/rSuiu_Hr.jpg'
    }
  },
  {
    id: 4,
    fullname: 'Ratchel Gun',
    slug: 'ratchel-gun',
    image: {
      alt: 'Image Ratchel Gun',
      url: 'https://images.unsplash.com/photo-1493666438817-866a91353ca9?ixlib=rb-0.3.5&q=80&fm=jpg&crop=entropy&cs=tinysrgb&w=200&fit=max&s=b616b2c5b373a80ffc9636ba24f7a4a9'
    }
  }
]

export const simpleCardData = [
  {
    id: 1,
    title: 'Data Science',
    slug: 'data-science',
    to: {
      name: 'group___en',
      params: {
        slug: 'data-science'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/200/480/320.jpg'
    }
  },
  {
    id: 2,
    title: 'History PECE',
    slug: 'history-pece',
    to: {
      name: 'group___en',
      params: {
        slug: 'history-pece'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/96/480/320.jpg'
    }
  },
  {
    id: 3,
    title: 'Empirical Group',
    slug: 'empirical',
    to: {
      name: 'group___en',
      params: {
        slug: 'empirical'
      }
    },
    image: null
  },
  {
    id: 4,
    title: 'Pece Users',
    slug: 'pece-users',
    to: {
      name: 'group___en',
      params: {
        slug: 'pece-users'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/222/480/320.jpg'
    }
  },
  {
    id: 5,
    title: 'Analyz Group',
    slug: 'analyze',
    to: {
      name: 'group___en',
      params: {
        slug: 'analyze'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/180/480/320.jpg'
    }
  },
  {
    id: 6,
    title: 'Open Group',
    slug: 'open-group',
    to: {
      name: 'group___en',
      params: {
        slug: 'open-group'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/80/480/320.jpg'
    }
  },
  {
    id: 7,
    title: 'EUA group',
    slug: 'eua-group',
    to: {
      name: 'group___en',
      params: {
        slug: 'eua-group'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/20/480/320.jpg'
    }
  },
  {
    id: 8,
    title: 'Data education',
    slug: 'data-education',
    to: {
      name: 'group___en',
      params: {
        slug: 'data-education'
      }
    },
    image: {
      alt: 'Image open group',
      url: 'https://i.picsum.photos/id/269/480/320.jpg'
    }
  }
]

export const discoverData = [
  {
    id: 2,
    title: 'Researcher audio artifact',
    slug: 'researcher-audio-artifact',
    __typename: 'ArtifactAudioConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-audio-artifact'
      }
    },
    image: null
  },
  {
    id: 3,
    title: 'Researcher sample artifact bundle',
    slug: 'researcher-sample-artifact-bundle',
    __typename: 'ArtifactBundleConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-sample-artifact-bundle'
      }
    },
    image: null
  },
  {
    id: 4,
    title: 'Normal user public image artifact',
    slug: 'normal-user-public-image-artifact',
    __typename: 'ArtifactImageConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'normal-user-public-image-artifact'
      }
    },
    image: null
  },
  {
    id: 5,
    title: `contributor's pdf artifact`,
    slug: 'contributors-pdf artifact',
    __typename: 'ArtifactPDFDocumentConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'contributors-pdf-artifact'
      }
    },
    image: null
  },
  {
    id: 6,
    title: 'Open text artifact but private to group',
    slug: 'open-text-artifact-but-private-to-group',
    __typename: 'ArtifactTextConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'open-text-artifact-but-private-to-group'
      }
    },
    image: null
  },
  {
    id: 7,
    title: 'Researcher sample video artifact',
    slug: 'researcher-sample-video-artifact',
    __typename: 'ArtifactVideoConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-sample-video-artifact'
      }
    },
    image: null
  },
  {
    id: 8,
    title: 'Researcher website artifact - open',
    slug: 'researcher-website-artifact---open',
    __typename: 'ArtifactWebsiteConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-website-artifact---open'
      }
    },
    image: null
  },
  {
    id: 9,
    title: 'Test group by researcher',
    slug: 'test-group-by-researcher',
    __typename: 'GroupConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'test-group-by-researcher'
      }
    },
    image: {
      alt: 'Test group by researcher',
      url: 'https://i.picsum.photos/id/200/480/320.jpg'
    }
  },
  {
    id: 10,
    title: 'Open memo in private group but made public',
    slug: 'open-memo-in-private-group-but-made-public',
    __typename: 'MemoConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'open-memo-in-private-group-but-made-public'
      }
    },
    image: null
  },
  {
    id: 11,
    title: `lindsay's new researcher pece essay`,
    slug: 'lindsays-new-researcher-pece-essay',
    __typename: 'PeceEssayConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'lindsays-new-researcher-pece-essay'
      }
    },
    image: null
  },
  {
    id: 12,
    title: 'Researcher photo essay [open no group]',
    slug: 'researcher-photo-essay-open-no-group',
    __typename: 'PhotoEssayConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-photo-essay-open-no-group'
      }
    },
    image: null
  },
  {
    id: 13,
    title: 'Researcher timeline essay',
    slug: 'researcher-timeline-essay',
    __typename: 'TimelineEssayConnection',
    to: {
      name: 'home___en',
      params: {
        slug: 'researcher-timeline-essay'
      }
    },
    image: null
  }
]

export const highlights = [
  {
    title: 'Platform for Experimental, Collaborative Ethnograph',
    images: {
      alt: 'teste',
      thumbnail: 'https://i.picsum.photos/id/421/480/320.jpg',
      medium: 'https://i.picsum.photos/id/421/640/480.jpg',
      large: 'https://i.picsum.photos/id/421/1280/400.jpg'
    },
    link: 'https://google.com',
    created_at: 'Dezember 31, 2019'
  },
  {
    title: 'Green Mountain National Forest',
    images: {
      alt: 'teste',
      thumbnail: 'https://i.picsum.photos/id/787/480/320.jpg',
      medium: 'https://i.picsum.photos/id/787/640/480.jpg',
      large: 'https://i.picsum.photos/id/787/1280/400.jpg'
    },
    link: 'https://facebook.com',
    created_at: 'April 26, 2019'
  },
  {
    title: 'The Amazon Rainforest',
    images: {
      alt: 'teste',
      thumbnail: 'https://i.picsum.photos/id/442/480/320.jpg',
      medium: 'https://i.picsum.photos/id/442/640/480.jpg',
      large: 'https://i.picsum.photos/id/442/1280/400.jpg'
    },
    link: 'https://trello.com',
    created_at: 'November 05, 2019'
  },
  {
    title: 'Arashiyama Bamboo Grove',
    images: {
      alt: 'teste',
      thumbnail: 'https://i.picsum.photos/id/454/480/320.jpg',
      medium: 'https://i.picsum.photos/id/454/640/480.jpg',
      large: 'https://i.picsum.photos/id/454/1280/400.jpg'
    },
    link: 'https://twitter.com',
    created_at: 'January 10, 2019'
  }
]

export const tagCard = [
  {
    id: 1,
    __typename: 'ArtifactAudioConnection',
    title: 'Artifact - audio',
    body: 'Doloremque diamlorem incidunt, repellendus expedita? Sollicitudin aptent pharetra provident? Praesentium, animi egestas netus. Justo ullam diam diam mattis aliquip nascetur aspernatur auctor pariatur repudiandae auctor, fusce? Occaecat, etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 2,
    __typename: 'ArtifactBundleConnection',
    title: 'Bundle test',
    body: 'Doloremque diamlorem incidunt, repellendus expedita? etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 3,
    __typename: 'ArtifactVideoConnection',
    title: 'Video test artifact lorem ipsum specially body',
    body: 'Doloremque diamlorem',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 4,
    __typename: 'ArtifactImageConnection',
    title: 'Album research PECE Ireland',
    body: 'Praesentium, animi egestas netus. Justo ullam diam diam mattis aliquip nascetur aspernatur auctor pariatur repudiandae auctor, fusce? Occaecat, etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 5,
    __typename: 'ArtifactPDFDocumentConnection',
    title: 'PDF file document with essay default documentation',
    body: 'Doloremque diamlorem incidunt, repellendus expedita? etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 6,
    __typename: 'ArtifactTextConnection',
    title: 'Text and more',
    body: 'Doloremque diamlorem',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 7,
    __typename: 'ArtifactWebsiteConnection',
    title: 'Website composition essay',
    body: 'Praesentium, nascetur aspernatur auctor pariatur repudiandae auctor, fusce? Occaecat, etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 8,
    __typename: 'GroupConnection',
    title: 'New group for new PECE website',
    body: 'Doloremque diamlorem incidunt, Doloremque diamlorem incidunt, Doloremque diamlorem incidunt, repellendus expedita? etiam, dolor dolore? Natus nostra, porro autem praesent',
    to: {
      name: 'home___en'
    }
  },
  {
    id: 9,
    __typename: 'PeceEssayConnection',
    title: 'Pece essay',
    body: 'Doloremque diamlorem, nascetur aspernatur auctor pariatur',
    to: {
      name: 'home___en'
    }
  }
]

export const icons = {
  ArtifactAudioConnection: 'audio',
  ArtifactBundleConnection: 'bundle',
  ArtifactImageConnection: 'photo',
  ArtifactPDFDocumentConnection: 'pdf-file',
  ArtifactTextConnection: 'text',
  ArtifactVideoConnection: 'video',
  ArtifactWebsiteConnection: 'web',
  GroupConnection: 'group',
  MemoConnection: 'memo',
  PeceEssayConnection: 'essay',
  PhotoEssayConnection: 'photo',
  TimelineEssayConnection: 'timeline'
}
